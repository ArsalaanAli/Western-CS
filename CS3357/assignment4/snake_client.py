import socket
import threading
import pygame
from cryptography.hazmat.backends import default_backend
from cryptography.hazmat.primitives.asymmetric import rsa, padding
from cryptography.hazmat.primitives import hashes, serialization

server_addr = 'localhost'
server_port = 5555

gameState = ""
instruction = "up"
messageSend = 0
sendState = True
width = 500  # Width of our screen
height = 500  # Height of our screen
rows = 20  # Amount of rows

client_private_key = ""
client_public_key = ""
server_public_key = ""


def redrawWindow(surface):
    global rows, width
    surface.fill((0, 0, 0))
    drawGrid(width, rows, surface)
    pygame.display.update()


def drawGrid(w, rows, surface):
    sizeBtwn = w // rows  # Gives us the distance between the lines

    x = 0  # Keeps track of the current x
    y = 0  # Keeps track of the current y
    for l in range(rows):  # We will draw one vertical and one horizontal line each loop
        x = x + sizeBtwn
        y = y + sizeBtwn

        pygame.draw.line(surface, (255, 255, 255), (x, 0), (x, w))
        pygame.draw.line(surface, (255, 255, 255), (0, y), (w, y))


def parseGameState():
    global gameState
    if gameState == "":
        return [[], []]
    snakes, snacks = gameState.split("|")
    snakes = snakes.split("**")
    playersArray = []
    for curSnake in snakes:
        snake = curSnake.split("*")
        snakeArray = []
        for snakeCube in snake:
            snakeTuple = None
            try:
                snakeTuple = eval(snakeCube)
            except:
                pass
            if snakeTuple:
                snakeArray.append(snakeTuple)
        playersArray.append(snakeArray)
    snacks = snacks.split("**")
    snackArray = []
    for snackCube in snacks:
        snackTuple = eval(snackCube)
        snackArray.append(snackTuple)
    return [playersArray, snackArray]


def drawCube(surface, pos, color, eyes=False):
    global width, rows
    dis = width // rows
    i = pos[0]
    j = pos[1]

    pygame.draw.rect(surface, color, (i*dis+1, j*dis+1, dis-2, dis-2))
    if eyes:
        centre = dis//2
        radius = 3
        circleMiddle = (i*dis+centre-radius, j*dis+8)
        circleMiddle2 = (i*dis + dis - radius*2, j*dis+8)
        pygame.draw.circle(surface, (0, 0, 0), circleMiddle, radius)
        pygame.draw.circle(surface, (0, 0, 0), circleMiddle2, radius)
    pygame.display.update()


def handleClient(client):
    global gameState, instruction, messageSend, sendState, server_public_key, client_private_key
    while True:
        try:
            if messageSend > 0:
                client.send(encrypt_message(
                    server_public_key, ("m"+str(messageSend))))
                client.settimeout(1)
                messageSend = 0
                sendState = False
            else:
                if sendState:
                    client.send(encrypt_message(
                        server_public_key, instruction))
                client.settimeout(1)
                message = client.recv(500)
                try:
                    message = message.decode('utf-8')
                except:
                    pass
                if message:
                    if message[0] == '(' or message[0] == '|':
                        gameState = message
                    else:
                        message = decrypt_message(client_private_key, message)
                        print(message[1::])
                        sendState = True
        except socket.timeout:
            pass
        except Exception as e:
            print(f"Error receiving message: {e}")
            break


def generate_keys():
    global client_private_key, client_public_key
    client_private_key = rsa.generate_private_key(
        public_exponent=65537,
        key_size=2048,
        backend=default_backend()
    )

    client_public_key = client_private_key.public_key()


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


def run():
    global width, rows, gameState, instruction, messageSend
    playerColors = [(255, 0, 0), (0, 255, 255), (255, 255, 255), (0, 0, 255),]

    win = pygame.display.set_mode((width, height))  # Creates our screen object

    clock = pygame.time.Clock()  # creating a clock object

    flag = True
    # STARTING MAIN LOOP
    while flag:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    instruction = "up"
                elif event.key == pygame.K_DOWN:
                    instruction = "down"
                elif event.key == pygame.K_RIGHT:
                    instruction = "right"
                elif event.key == pygame.K_LEFT:
                    instruction = "left"
                elif event.key == pygame.K_z:
                    messageSend = 1
                elif event.key == pygame.K_x:
                    messageSend = 2
                elif event.key == pygame.K_c:
                    messageSend = 3
            # if event is of type quit then set
            # running bool to false
            if event.type == pygame.QUIT:
                running = False
        # This will delay the game so it doesn't run too quickly
        pygame.time.delay(50)
        clock.tick(10)  # Will ensure our game runs at 10 FPS
        redrawWindow(win)  # This will refresh our screen
        curGameState = parseGameState()
        for player, playerPos in enumerate(curGameState[0]):
            for i, snakeCube in enumerate(playerPos):
                if i == 0:
                    drawCube(win, snakeCube, playerColors[player], True)
                else:
                    drawCube(win, snakeCube, playerColors[player])
        for snackCube in curGameState[1]:
            drawCube(win, snackCube, (0, 255, 0))


generate_keys()
public_key_bytes = client_public_key.public_bytes(
    encoding=serialization.Encoding.PEM,
    format=serialization.PublicFormat.SubjectPublicKeyInfo
)
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # TCP
client_socket.connect((server_addr, server_port))
client_socket.send(public_key_bytes)
serverKeyRecv = client_socket.recv(4096)
server_public_key = serialization.load_pem_public_key(
    serverKeyRecv, backend=default_backend())
client_thread = threading.Thread(
    target=handleClient, args=(client_socket,))
client_thread.start()
run()
