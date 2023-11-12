import socket
import threading
import pygame

server_addr = 'localhost'
server_port = 5555

gameState = ""
direction = "up"
width = 500  # Width of our screen
height = 500  # Height of our screen
rows = 20  # Amount of rows


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
    snake, snacks = gameState.split("|")
    snake = snake.split("*")
    snakeArray = []
    for snakeCube in snake:
        snakeTuple = eval(snakeCube)
        snakeArray.append(snakeTuple)
    snacks = snacks.split("**")
    snackArray = []
    for snackCube in snacks:
        snackTuple = eval(snackCube)
        snackArray.append(snackTuple)
    return [snakeArray, snackArray]


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
    global gameState, direction
    while True:
        try:
            client.send(direction.encode('utf-8'))
            client.settimeout(1)
            message = client.recv(500).decode('utf-8')
            if message:
                gameState = message
        except socket.timeout:
            pass
        except Exception as e:
            print(f"Error receiving message: {e}")
            break


def run():
    global width, rows, gameState, direction

    win = pygame.display.set_mode((width, height))  # Creates our screen object

    clock = pygame.time.Clock()  # creating a clock object

    flag = True
    # STARTING MAIN LOOP
    while flag:
        for event in pygame.event.get():
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_UP:
                    direction = "up"
                elif event.key == pygame.K_DOWN:
                    direction = "down"
                elif event.key == pygame.K_RIGHT:
                    direction = "right"
                elif event.key == pygame.K_LEFT:
                    direction = "left"
            # if event is of type quit then set
            # running bool to false
            if event.type == pygame.QUIT:
                running = False
        # This will delay the game so it doesn't run too quickly
        pygame.time.delay(50)
        clock.tick(10)  # Will ensure our game runs at 10 FPS
        redrawWindow(win)  # This will refresh our screen
        curGameState = parseGameState()
        for i, snakeCube in enumerate(curGameState[0]):
            if i == 0:
                drawCube(win, snakeCube, (255, 0, 0), True)
            else:
                drawCube(win, snakeCube, (255, 0, 0))
        for snackCube in curGameState[1]:
            drawCube(win, snackCube, (0, 255, 0))


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # TCP
client_socket.connect((server_addr, server_port))
client_thread = threading.Thread(
    target=handleClient, args=(client_socket,))
client_thread.start()
run()
