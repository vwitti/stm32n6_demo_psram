//Unten ist ein einfaches Echo-Client/Server-Beispiel in C mit dem BSD Sockets Interface (TCP, IPv4).
//Der Server nimmt Verbindungen an und echo’t alles zurück; der Client sendet Zeilen und zeigt die Antwort.
// echoclient.c
#define _POSIX_C_SOURCE 200112L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#if defined(__GNUC__) && (__ARM_ARCH == 8)

// GCC targeting ARM architecute 8 (z.B. Cortex-M55)
#if defined(OS_TYPE_THREADX)

#include "Common/Inc/Test/bsd_tcp_echo.h"
#include "Common/Inc/Init/app_netxduo_bsd_api.h"
#define REAL_MAIN_STATIC static
REAL_MAIN_STATIC int real_main(int argc, char **argv);

int demo_bsd_tcp_echo_client_main(const char *prog, const char *server_ip, const char *port)
{
    char *argv[4];

    argv[0] = (char *)prog;
    argv[1] = (char *)server_ip;
    argv[2] = (char *)port;
    argv[3] = NULL;

    return real_main(3, argv);
}

#endif // OS_TYPE_THREADX

#endif // defined(__GNUC__) && (__ARM_ARCH == 8)

#if defined(__GNUC__) && ((__x86_64__ == 1) || (__amd64__ == 1))

// GCC targeting x86_64
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define REAL_MAIN_STATIC
#define real_main main
#endif //defined(__GNUC__) && defined(__x86_64__)

static void die(const char *msg) {
    perror(msg);
    exit(EXIT_FAILURE);
}

REAL_MAIN_STATIC int real_main(int argc, char **argv) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <server-ip> <port>\nExample: %s 127.0.0.1 12345\n",
                argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    const char *ip = argv[1];
    int port = atoi(argv[2]);
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) die("socket");

    struct sockaddr_in srv;
    memset(&srv, 0, sizeof(srv));
    srv.sin_family = AF_INET;
    srv.sin_port = htons((uint16_t)port);
    if (inet_pton(AF_INET, ip, &srv.sin_addr) != 1) {
        fprintf(stderr, "Invalid IP address: %s\n", ip);
        close(fd);
        return EXIT_FAILURE;
    }

    if (connect(fd, (struct sockaddr *)&srv, sizeof(srv)) < 0) die("connect");

    printf("Connected to %s:%d\nType a line and press Enter (Ctrl+D to quit)\n", ip, port);

    char line[4096];
    while (fgets(line, sizeof(line), stdin) != NULL) {
        size_t len = strlen(line);

        // Senden (mit Loop)
        size_t off = 0;
        while (off < len) {
            ssize_t n = send(fd, line + off, len - off, 0);
            if (n < 0) {
                if (errno == EINTR) continue;
                die("send");
            }
            off += (size_t)n;
        }

        // Echo empfangen: hier nehmen wir an, dass eine "Zeile" zurückkommt.
        // Für ein robustes Protokoll würdest du framing/Delimiter sauber behandeln.
        ssize_t r = recv(fd, line, sizeof(line) - 1, 0);
        if (r == 0) {
            fprintf(stderr, "Server closed connection\n");
            break;
        }
        if (r < 0) {
            if (errno == EINTR) continue;
            die("recv");
        }
        line[r] = '\0';
        fputs("echo: ", stdout);
        fputs(line, stdout);
    }

    close(fd);
    return 0;
}
