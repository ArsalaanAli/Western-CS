import socket
import threading
import pygame

server_addr = 'localhost'
server_port = 5555

gameState = [[], []]


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


def drawCube():
    global width, rows
    dis = width // rows

# pos = (10, 10)


def parseGameState(state):
    if state == "":
        return
    global gameState
    snake, snacks = state.split("|")
    snake = snake.split("*")
    snakeArray = []
    for snakeCube in snake:
        snakeTuple = eval(snakeCube)
        snakeArray.append(snakeTuple)
    gameState[0] = snakeArray
    snacks = snacks.split("**")
    snackArray = []
    for snackCube in snacks:
        snackTuple = eval(snackCube)
        snackArray.append(snackTuple)
    gameState[1].append(snackArray)
    print(gameState, "PARSED GAME STATE")


def displayGame():
    global width, rows
    width = 500  # Width of our screen
    height = 500  # Height of our screen
    rows = 20  # Amount of rows

    win = pygame.display.set_mode((width, height))  # Creates our screen object

    clock = pygame.time.Clock()  # creating a clock object

    flag = True
    # STARTING MAIN LOOP
    while flag:
        # This will delay the game so it doesn't run too quickly
        pygame.time.delay(50)
        clock.tick(10)  # Will ensure our game runs at 10 FPS
        redrawWindow(win)  # This will refresh our screen


def run(client):
    print("running")
    while True:
        try:
            print("sending")
            client.send("get".encode('utf-8'))
            print("receiving")
            message = client.recv(1024).decode('utf-8')
            if message:
                parseGameState(message)
        except Exception as e:
            print(f"Error receiving message: {e}")
            break


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # TCP
client_socket.connect((server_addr, server_port))

run(client_socket)
