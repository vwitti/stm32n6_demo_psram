#!/usr/bin/env python3
import socket

HOST = "0.0.0.0"   # auf alle Interfaces hören
PORT = 11111       # Syslog-UDP-Port
   
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
sock.bind((HOST, PORT))

print(f"Check if port {PORT} is enabled by your firewall, e.g. sudo ufw allow {PORT}/udp")
print(f"Listen to UDP {HOST}:{PORT} ... (Strg+C zum Beenden)")

while True:
    data, addr = sock.recvfrom(65535)  # max UDP-Paketgröße
    try:
        text = data.decode("utf-8", errors="replace")
    except Exception as e:
        text = repr(data)
    print(f"[{addr[0]}:{addr[1]}] {text.strip()}")
