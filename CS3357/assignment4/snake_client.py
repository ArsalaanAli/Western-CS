import socket
import threading
import pygame

server_addr = 'localhost'
server_port = 5555

gameState = ""
instruction = "up"
messageSend = 0
sendState = True
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
                print(snakeCube, "ERROR HERE")
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
    global gameState, instruction, messageSend, sendState
    while True:
        try:
            if messageSend > 0:
                client.send(("m"+str(messageSend)).encode('utf-8'))
                messageSend = 0
                sendState = False
            else:
                if sendState:
                    client.send(instruction.encode('utf-8'))
                client.settimeout(1)
                message = client.recv(500).decode('utf-8')
                if message:
                    if message[0] == 'M':
                        print(message[1::])
                        sendState = True
                    else:
                        gameState = message
        except socket.timeout:
            pass
        except Exception as e:
            print(f"Error receiving message: {e}")
            break


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


client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)  # TCP
client_socket.connect((server_addr, server_port))
client_thread = threading.Thread(
    target=handleClient, args=(client_socket,))
client_thread.start()
run()
