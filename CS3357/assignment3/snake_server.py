import numpy as np
import socket
from _thread import *
import pickle
from snake import SnakeGame
import uuid
import time

# server = "10.11.250.207"
server = "localhost"
port = 5555
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

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


def main():
    global counter, game

    conn, addr = s.accept()
    print("Connected to:", addr)

    unique_id = str(uuid.uuid4())
    color = rgb_colors_list[np.random.randint(0, len(rgb_colors_list))]
    game.add_player(unique_id, color=color)

    start_new_thread(game_thread, ())

    print(game_state)
    while True:
        print("receiving")
        data = conn.recv(500).decode()
        print("sending")
        conn.send(game_state.encode())

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

        elif data in ["up", "down", "left", "right"]:
            move = data
            moves_queue.add((unique_id, move))
        else:
            print("Invalid data received from client:", data)

    conn.close()


if __name__ == "__main__":
    main()
