# import socket
# import threading
# import sys

# # Define the function to handle client requests
# def handle_client(clientSocket):
#         print("HANDLING")
#         while True:
#             request_data = clientSocket.recv(1024).decode()
#             if not request_data or request_data == '':
#                 print("Client Disconnected")
#                 clientSocket.close()
#             # Check if the request is a GET request
#             if "GET" in request_data:
#                 print("GET REQUEST")
#                 response = "HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nHello"
#                 clientSocket.send(response.encode())
                
# #Get port and max_connections from commandline arguments
# if len(sys.argv) != 3:
#     print("Usage: python server.py <host> <port>")
#     sys.exit(1)

# PORT = int(sys.argv[1])
# MAX_CONNECTIONS = int(sys.argv[2])
# # Create a socket server
# serverSocket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
# serverSocket.bind(("", 8080))
# serverSocket.listen(MAX_CONNECTIONS)

# print("Server started on port 8080...")

# while True:
#     client, addr = serverSocket.accept()
#     print(f"Accepted connection from {addr[0]}:{addr[1]}")
#     client_handler = threading.Thread(target=handle_client, args=(client,))
#     client_handler.start()

import socket
import threading

# Define the host and port
HOST = '127.0.0.1'  # Use '0.0.0.0' to listen on all available network interfaces
PORT = 8080

# Create a socket
server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Bind the socket to the address
server_socket.bind((HOST, PORT))

# Listen for incoming connections
server_socket.listen(5)
print(f"Server is listening on {HOST}:{PORT}")

# Function to handle a client connection
def handle_client(client_socket, client_address):
    print(f"Accepted connection from {client_address}")

    while True:
        # Receive data from the client
        data = client_socket.recv(1024)
        if not data:
            break  # Client disconnected

        # Process the received data (you can implement your logic here)
        response = b"Hello, client! You said: " + data

        # Send a response back to the client
        client_socket.send(response)

    # Close the client socket when the client disconnects
    print(f"Connection from {client_address} closed")
    client_socket.close()

# Main server loop
while True:
    # Accept a client connection
    client_socket, client_address = server_socket.accept()

    # Create a new thread to handle the client
    client_thread = threading.Thread(target=handle_client, args=(client_socket, client_address))
    client_thread.start()
