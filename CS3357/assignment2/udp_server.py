import socket
import threading

# Create a UDP socket
server = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server.bind(('0.0.0.0', 12345))  # Replace with your desired host and port

# Dictionary to store client addresses
clients = {}

# Function to handle incoming messages


def handle_messages():
    while True:
        message, client_address = server.recvfrom(1024)
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
                    server.sendto(
                        f"{sender_name}: {message}".encode('utf-8'), address)


# Start a thread to handle incoming messages
thread = threading.Thread(target=handle_messages)
thread.start()

# Main server loop (optional, you can perform other tasks here if needed)
while True:
    pass
