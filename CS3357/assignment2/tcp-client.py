import socket
import threading


def receive_messages(client):
    while True:
        try:
            message = client.recv(1024).decode('utf-8')
            if message:
                print(
                    "\u001B[s"             # Save current cursor position
                    "\u001B[A"             # Move cursor up one line
                    "\u001B[999D"          # Move cursor to beginning of line
                    "\u001B[S"             # Scroll up/pan window down 1 line
                    "\u001B[L",            # Insert new line
                    end="")
                print(message, end="")        # Print message line
                # Move back to the former cursor position
                print("\u001B[u", end="")
                print("", end="", flush=True)  # Flush message
        except Exception as e:
            print(f"Error receiving message: {e}")
            break


# Get the user's username
username = input("Enter your username: ")

# Create a socket for the client
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# Connect to the server
server_ip = '127.0.0.1'  # Replace with the server's IP address or hostname
server_port = 9301       # Replace with the server's port
client.connect((server_ip, server_port))
client.send(username.encode('utf-8'))

# Start a thread to handle incoming messages
receive_thread = threading.Thread(target=receive_messages, args=(client,))
receive_thread.start()

# Start sending messages
while True:
    message = input(username + ": ")
    client.send(message.encode('utf-8'))
