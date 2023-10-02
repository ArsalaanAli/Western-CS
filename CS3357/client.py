from socket import socket, AF_INET, SOCK_STREAM
import sys

if len(sys.argv) != 3:
    print("Usage: python server.py <host> <port>")
    sys.exit(1)

# Define the host and port to listen on
HOST = '127.0.0.1'
PORT = int(sys.argv[1])
ROUTE = sys.argv[2]


clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((HOST, PORT))
print("Connection established")

httpRequest = f"GET /{ROUTE} HTTP/1.1\r\nHost: {HOST}\r\n\r\n"

clientSocket.send(httpRequest.encode())

data = clientSocket.recv(1024).decode()
head, html = data.split("\r\n\r\n")
responseCode = head.split()[1]

if responseCode == "200":
    with open(ROUTE, "w") as file:
        file.write(html)

elif responseCode == "404":
    print("404 not found")
clientSocket.close()
