import socket
import threading

# Create a socket for the server
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind(('0.0.0.0', 4000))  # Replace with your desired host and port
server.listen()

# Lists to store client connections and their usernames
clients = []
usernames = []

# Function to broadcast messages to all clients


def broadcast(message, client):
    for c in clients:
        if c != client:
            try:
                c.send(message)
            except Exception as e:
                # Handle exceptions and remove the disconnected client
                print(f"Error broadcasting message to a client: {e}")
                index = clients.index(c)
                clients.pop(index)
                c.close()
                username = usernames[index]
                usernames.pop(index)
                broadcast(f"{username} has left the chat.".encode(
                    'utf-8'), server)

# Function to handle client connections


def handle_client(client):
    while True:
        try:
            message = client.recv(1024).decode('utf-8')
            if not message:
                break
            message = usernames[clients.index(client)] + ": " + message
            print(message)
            broadcast(message.encode('utf-8'), client)
        except Exception as e:
            # Handle exceptions and remove the disconnected client
            print(f"Error receiving message from a client: {e}")
            index = clients.index(client)
            clients.pop(index)
            client.close()
            username = usernames[index]
            usernames.pop(index)
            broadcast(f"{username} has left the chat.".encode('utf-8'), server)
            break


# Accept and handle multiple client connections
while True:
    client, address = server.accept()
    print(f"Connected with {str(address)}")

    # Request and store the client's username
    username = client.recv(1024).decode('utf-8')
    usernames.append(username)
    clients.append(client)

    # Notify all clients about the new user
    print(f"{username} has joined the chat.")
    broadcast(f"{username} has joined the chat.".encode('utf-8'), client)

    # Start a thread to handle the client's messages
    thread = threading.Thread(target=handle_client, args=(client,))
    thread.start()
