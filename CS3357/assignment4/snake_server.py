import numpy as np
import socket
from _thread import *
import pickle
from snake import SnakeGame
import uuid
import time
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes, serialization

# server = "10.11.250.207"
server = "localhost"
port = 5555
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_private_key = ""
server_public_key = ""


counter = 0
rows = 20

try:
    s.bind((server, port))
except socket.error as e:
    str(e)

s.listen(2)
# s.settimeout(0.5)
print("Waiting for a connection, Server Started")


game = SnakeGame(rows)
game_state = ""
last_move_timestamp = time.time()
interval = 0.2
moves_queue = set()
clientList = []
clientKeys = []


def game_thread():
    global game, moves_queue, game_state
    while True:
        last_move_timestamp = time.time()
        game.move(moves_queue)
        moves_queue = set()
        game_state = game.get_state()
        while time.time() - last_move_timestamp < interval:
            time.sleep(0.1)


rgb_colors = {
    "red": (255, 0, 0),
    "green": (0, 255, 0),
    "blue": (0, 0, 255),
    "yellow": (255, 255, 0),
    "orange": (255, 165, 0),
}
rgb_colors_list = list(rgb_colors.values())


def broadcast(message, public_key):
    global clientList, server_private_key
    for i, c in enumerate(clientList):
        try:
            print("BROADCASTING")
            c.send(encrypt_message(public_key, message))
        except Exception as e:
            print(e, "COULD NOT SEND MESSAGE")
            pass


def handle_client(client, public_key):
    global counter, game, clientKeys
    unique_id = str(uuid.uuid4())
    color = rgb_colors_list[np.random.randint(0, len(rgb_colors_list))]
    game.add_player(unique_id, color=color)
    messageOptions = ["Hi there!", "Nice snake!", "Oops, I died!"]
    while True:
        data = client.recv(500)
        data = decrypt_message(server_private_key, data)
        client.send(game_state.encode())

        move = None
        if not data:
            print("no data received from client")
            break
        elif data == "get":
            print("received get")
            pass
        elif data == "quit":
            print("received quit")
            game.remove_player(unique_id)
            break
        elif data == "reset":
            game.reset_player(unique_id)
        elif data == "m1":
            broadcast("M"+unique_id+": " + messageOptions[0], public_key)
        elif data == "m2":
            broadcast("M"+unique_id+": " + messageOptions[1], public_key)
        elif data == "m3":
            broadcast("M"+unique_id+": " + messageOptions[2], public_key)
        elif data in ["up", "down", "left", "right"]:
            move = data
            moves_queue.add((unique_id, move))
        else:
            print("Invalid data received from client:", data)


def generate_keys():
    global server_private_key, server_public_key
    server_private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
        backend=default_backend()
    )

    server_public_key = server_private_key.public_key()


def encrypt_message(public_key, message):
    ciphertext = public_key.encrypt(
        message.encode('utf-8'),
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    return ciphertext


def decrypt_message(private_key, ciphertext):
    plaintext = private_key.decrypt(
        ciphertext,
        padding.OAEP(
            mgf=padding.MGF1(algorithm=hashes.SHA256()),
            algorithm=hashes.SHA256(),
            label=None
        )
    )
    return plaintext.decode('utf-8')


def main():
    global counter, game, clientList, clientKeys, server_private_key, server_public_key
    generate_keys()
    # emessage = "test"
    # encryption = encrypt_message(server_public_key, emessage)
    # decrpty = decrypt_message(server_private_key, encryption)
    public_key_bytes = server_public_key.public_bytes(
        encoding=serialization.Encoding.PEM,
        format=serialization.PublicFormat.SubjectPublicKeyInfo
    )

    start_new_thread(game_thread, ())
    while True:
        conn, addr = s.accept()
        print("Connected to:", addr)
        clientList.append(conn)
        clientPubKeyRecv = conn.recv(4096)
        client_public_key = serialization.load_pem_public_key(
            clientPubKeyRecv, backend=default_backend())
        conn.send(public_key_bytes)
        start_new_thread(handle_client, (conn, client_public_key,))


if __name__ == "__main__":
    main()
