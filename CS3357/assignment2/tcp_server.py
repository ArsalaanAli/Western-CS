# Assignment: TCP Simple Chat Room - TCP Server Code Implementation

# **Libraries and Imports**:
#    - Import the required libraries and modules.
#    You may need socket, threading, select, time libraries for the client.
#    Feel free to use any libraries as well.
import socket
import threading

# **Global Variables**:
#    - IF NEEDED, Define any global variables that will be used throughout the code.
clients = []  # list to add the connected client sockets , feel free to adjust it to other place
usernames = []

# **Function Definitions**:
#    - In this section, you will implement the functions you will use in the server side.
#    - Feel free to add more other functions, and more variables.
#    - Make sure that names of functions and variables are meaningful.


def broadcast(message, client, server):
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
                    'utf-8'), server, server)


def handle_client(client, server):
    while True:
        try:
            message = client.recv(1024).decode('utf-8')
            if not message:
                break
            message = usernames[clients.index(client)] + ": " + message
            print(message)
            broadcast(message.encode('utf-8'), client, server)
        except Exception as e:
            # Handle exceptions and remove the disconnected client
            print(f"Error receiving message from a client: {e}")
            index = clients.index(client)
            clients.pop(index)
            client.close()
            username = usernames[index]
            usernames.pop(index)
            broadcast(f"{username} has left the chat.".encode(
                'utf-8'), client, server)
            break


def run(serverSocket, serverPort):
    while True:
        client, address = serverSocket.accept()
        print(f"Connected with {str(address)}")

        # Request and store the client's username
        username = client.recv(1024).decode('utf-8')
        usernames.append(username)
        clients.append(client)

        # Notify all clients about the new user
        print(f"{username} has joined the chat.")
        broadcast(f"{username} has joined the chat.".encode(
            'utf-8'), client, serverSocket)

        # Start a thread to handle the client's messages
        thread = threading.Thread(
            target=handle_client, args=(client, serverSocket, ))
        thread.start()


# **Main Code**:
if __name__ == "__main__":
    server_port = 9301
    # Creating a TCP socket.
    print("starting server")
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', server_port))
    # size of the waiting_queue that stores the incoming requests to connect.
    server_socket.listen(3)
    print("server running on port", server_port)

    # please note that listen() method is NOT for setting the maximum clients to connect to server.
    # didnt get it? basically, when the process (assume process is man that execute the code line by line) is executing the accept() method on the server side,
    # the process holds or waits there until a client sends a request to connect and then the process continue executing the rest of the code.
    # good! what if there is another client wants to connect and the process on the server side isnt executing the accept() method at the same time,
    # Now listen() method joins the party to solve this issue, it lets the incoming requests from the other clients to be stored in a queue or list until the process execute the accept() method.
    # the size of the queue is set using listen(size). IF YOU STILL DONT GET IT, SEND ME AN EMAIL.

    # Calling the function to start the server.
    run(server_socket, server_port)
