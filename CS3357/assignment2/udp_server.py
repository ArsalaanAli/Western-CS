# Assignment: UDP Simple Chat Room - UDP Server Code Implementation

# **Libraries and Imports**:
#    - Import the required libraries and modules.
#    You may need socket, select, time libraries for the client.
#    Feel free to use any libraries as well.
import socket
import threading

# **Global Variables**:
#    - IF NEEDED, Define any global variables that will be used throughout the code.
clients = {}

# **Function Definitions**:
#    - In this section, you will implement the functions you will use in the server side.
#    - Feel free to add more other functions, and more variables.
#    - Make sure that names of functions and variables are meaningful.


def run(serverSocket, serverPort):
    serverSocket.bind(('127.0.0.1', serverPort))
    print("server started on port", serverPort)
    while True:
        message, client_address = serverSocket.recvfrom(1024)
        message = message.decode('utf-8')
        if client_address not in clients:
            clients[client_address] = message
            print(f"{message} has joined the chat.")
        else:
            sender_name = clients[client_address]
            print(f"{sender_name}: {message}")
            # Broadcast the message to all clients except the sender
            for address in clients:
                if address != client_address:
                    serverSocket.sendto(
                        f"{sender_name}: {message}".encode('utf-8'), address)


# **Main Code**:
if __name__ == "__main__":
    # Set the `serverPort` to the desired port number (e.g., 9301).
    serverPort = 9301
    # Creating a UDP socket.
    serverSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    run(serverSocket, serverPort)  # Calling the function to start the server.
