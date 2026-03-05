//Unten ist ein einfaches Echo-Client/Server-Beispiel in C mit dem BSD Sockets Interface (TCP, IPv4).
//Der Server nimmt Verbindungen an und echo’t alles zurück; der Client sendet Zeilen und zeigt die Antwort.
// echoserver.c
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
#define INET_ADDRSTRLEN 16
#define REAL_MAIN_STATIC static
REAL_MAIN_STATIC int real_main(int argc, char **argv);
#define LISTEN_BACKLOG		2		// Must be less than NX_BSD_MAX_LISTEN_BACKLOG
int demo_bsd_tcp_echo_server_main(const char *prog, const char *port)
{
    char *argv[3];

    argv[0] = (char *)prog;
    argv[1] = (char *)port;
    argv[2] = NULL;

    return real_main(2, argv);
}

#endif // OS_TYPE_THREADX

#endif // defined(__GNUC__) && (__ARM_ARCH == 8)

#if defined(__GNUC__) && ((__x86_64__ == 1) || (__amd64__ == 1))

// GCC targeting x86_64
#include <signal.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#define REAL_MAIN_STATIC
#define real_main main
#define LISTEN_BACKLOG		16
#endif

static void die(const char *msg) {
    perror(msg);
    printf("-----------------\n");
    exit(EXIT_FAILURE);
}

REAL_MAIN_STATIC int real_main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <port>\nExample: %s 12345\n", argv[0], argv[0]);
        return EXIT_FAILURE;
    }

    int port = atoi(argv[1]);
    if (port <= 0 || port > 65535) {
        fprintf(stderr, "Invalid port: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    // Optional: SIGPIPE ignorieren, damit send()/write() nicht das Programm beendet,
    // wenn der Client die Verbindung geschlossen hat.
#if defined(__GNUC__) && defined(__x86_64__)
    signal(SIGPIPE, SIG_IGN);
#endif

    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) die("socket");

    int yes = 1;
    if (setsockopt(listen_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) < 0)
        die("setsockopt(SO_REUSEADDR)");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons((uint16_t)port);

    if (bind(listen_fd, (struct sockaddr *)&addr, sizeof(addr)) < 0) {
    	die("bind");
    }
    if (listen(listen_fd, LISTEN_BACKLOG) < 0) {
    	die("listen");
    }

    printf("Echo server listening on 0.0.0.0:%d\n", port);

    for (;;) {
        struct sockaddr_in peer;
        socklen_t peer_len = sizeof(peer);

        int client_fd = accept(listen_fd, (struct sockaddr *)&peer, &peer_len);
        if (client_fd < 0) {
            if (errno == EINTR) continue;
            die("accept");
        }

        char peer_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &peer.sin_addr, peer_ip, sizeof(peer_ip));
        printf("Client connected: %s:%u\n", peer_ip, ntohs(peer.sin_port));

        char buf[4096];
        for (;;) {
            ssize_t n = recv(client_fd, buf, sizeof(buf), 0);
            if (n == 0) {
                printf("Client disconnected: %s:%u\n", peer_ip, ntohs(peer.sin_port));
                break;
            }
            if (n < 0) {
                if (errno == EINTR) continue;
                perror("recv");
                break;
            }

            // Echo zurück (mit Loop, falls send() nur teilweise schreibt)
            ssize_t sent = 0;
            while (sent < n) {
                ssize_t m = send(client_fd, buf + sent, (size_t)(n - sent), 0);
                if (m < 0) {
                    if (errno == EINTR) continue;
                    perror("send");
                    sent = -1;
                    break;
                }
                sent += m;
            }
            if (sent < 0) break;
        }

        close(client_fd);
    }

    close(listen_fd);
    return 0;
}
