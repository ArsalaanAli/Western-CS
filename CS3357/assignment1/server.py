from socket import socket, AF_INET, SOCK_STREAM
import threading
import os
import sys

if len(sys.argv) != 3:
    print("Usage: python server.py <host> <port>")
    sys.exit(1)


# Define the host and port to listen on
HOST = '127.0.0.1'
PORT = int(sys.argv[1])
MAX_CONNECTIONS = int(sys.argv[2])


# Create a socket object
serverSocket = socket(AF_INET, SOCK_STREAM)

# Bind the socket to the host and port
serverSocket.bind((HOST, PORT))

# Listen for incoming connections
serverSocket.listen(MAX_CONNECTIONS)
print(f"Listening on {HOST}:{PORT}")


def handleClient(clientSocket):
    # Receive the HTTP request
    while True:
        try:
            request = clientSocket.recv(1024).decode()
            # Check if the request is a GET request
            if request.startswith('GET'):
                response = 'HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n'
                urlRoute = request.split('\n')[0].split()[1].strip("/")
                fileName = urlRoute
                if os.path.exists(fileName):
                    with open(fileName, 'r') as htmlDoc:
                        htmlContent = htmlDoc.read()
                    response += htmlContent
                    clientSocket.send(response.encode())
                else:
                    response = "HTTP/1.1 404 Not Found\r\n\r\n404 Not Found"
                    clientSocket.send(response.encode())
                # Send an HTTP response
            if not request:
                break
        except Exception as e:
            response = "HTTP/1.1 404 Not Found\r\n\r\n404 Not Found"
            clientSocket.send(response.encode())
            break
    print("Client Disconnected")
    clientSocket.close()


while True:
    # Accept incoming connection
    clientSocket, clientAddress = serverSocket.accept()
    print("Client Connected")
    # handleClient(clientSocket)
    clientHandler = threading.Thread(
        target=handleClient, args=(clientSocket, ))
    clientHandler.start()
