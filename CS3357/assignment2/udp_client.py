import socket
import threading

# Function to receive and display messages


def receive_messages():
    while True:
        try:
            message, server_address = client.recvfrom(1024)
            if message:
                print(
                    "\u001B[s"             # Save current cursor position
                    "\u001B[A"             # Move cursor up one line
                    "\u001B[999D"          # Move cursor to beginning of line
                    "\u001B[S"             # Scroll up/pan window down 1 line
                    "\u001B[L",            # Insert new line
                    end="")
                # Print message line
                print(message.decode('utf-8'), end="")
                # Move back to the former cursor position
                print("\u001B[u", end="")
                print("", end="", flush=True)  # Flush message
        except Exception as e:
            print(f"Error receiving message: {e}")
            break


# Get the user's username
username = input("Enter your username: ")

# Create a socket for the client
client = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
client.bind(('0.0.0.0', 0))  # Bind to a random available local port

# Server address and port
server_ip = '127.0.0.1'  # Replace with the server's IP address or hostname
server_port = 9301       # Replace with the server's port

# Start a thread to handle incoming messages
receive_thread = threading.Thread(target=receive_messages)
receive_thread.start()

# Join the chatroom by sending the username to the server
client.sendto(username.encode('utf-8'), (server_ip, server_port))

# Start sending messages
while True:
    message = input(username + ": ")
    client.sendto(message.encode('utf-8'), (server_ip, server_port))
