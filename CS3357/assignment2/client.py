# Assignment: TCP Simple Chat Room - TCP Client Code Implementation

# **Libraries and Imports**:
#    - Import the required libraries and modules.
#    You may need sys, socket, argparse, select, threading (or _thread) libraries for the client implementation.
#    Feel free to use any libraries as well.
import argparse
import socket
import threading

# **Global Variables**:
#    - IF NEEDED, Define any global variables that will be used throughout the code.

# **Function Definitions**:
#    - In this section, you will implement the functions you will use in the client side.
#    - Feel free to add more other functions, and more variables.
#    - Make sure that names of functions and variables are meaningful.
#    - Take into consideration error handling, interrupts,and client shutdown.


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


def run(clientSocket, clientname):
    clientSocket.send(clientname.encode('utf-8'))

    # Start a thread to handle incoming messages
    receive_thread = threading.Thread(
        target=receive_messages, args=(clientSocket,))
    receive_thread.start()

    # Start sending messages
    while True:
        message = input(clientname + ": ")
        clientSocket.send(message.encode('utf-8'))
    pass


# **Main Code**:
if __name__ == "__main__":
    parser = argparse.ArgumentParser(description='Argument Parser')
    parser.add_argument('name')  # to use: python tcp_client.py username
    args = parser.parse_args()
    client_name = args.name
    server_addr = '127.0.0.1'
    server_port = 9301

    client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # TCP
    client_socket.connect((server_addr, server_port))

    run(client_socket, client_name)
