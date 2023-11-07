# Assignment: UDP Simple Chat Room - UDP Client Code Implementation

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


def run(clientSocket, clientName, serverAddr, serverPort):
    # The main client function.
    clientSocket.bind(('0.0.0.0', 0))  # Bind to a random available local port
    receive_thread = threading.Thread(
        target=receive_messages, args=(clientSocket,))
    receive_thread.start()
    clientSocket.sendto(clientName.encode('utf-8'), (serverAddr, serverPort))

    # Start sending messages
    while True:
        message = input(clientName + ": ")
        clientSocket.sendto(message.encode('utf-8'), (serverAddr, serverPort))


# **Main Code**:
if __name__ == "__main__":

    # Arguments: name address
    parser = argparse.ArgumentParser(description='argument parser')
    parser.add_argument('name')  # to use: python udp_client.py username
    args = parser.parse_args()
    clientname = args.name
    serverAddr = '127.0.0.1'
    serverPort = 9301
    clientSocket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)  # UDP

    # Calling the function to start the client.
    run(clientSocket, clientname, serverAddr, serverPort)
