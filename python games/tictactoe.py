import pygame as pg
import time
import os
#from minmax import Minmax

# -------------------------- Define Variables --------------------------
# Initialize pygame
pg.init()

# Define screen dimensions
width = 400
height = 400

# Define colours
white = (255, 255, 255)
black = (0, 0, 0)

# Initialize flags
done = False

# Store the current turn
XO = 'X'

# Store the winner
winner = None

# Initialize the draw flag
draw = None

# Create 2D array to store board values
board = [[None] * 3, [None] * 3, [None] * 3]

# Import assets
path = os.path.dirname(__file__)
assets = os.path.join(path, 'assets')
x_img = pg.image.load(os.path.join(assets, "x.png"))
y_img = pg.image.load(os.path.join(assets, "o.png"))

# resize images
x_img = pg.transform.scale(x_img, (80, 80))
o_img = pg.transform.scale(y_img, (80, 80))

# Create the game screen4
screen = pg.display.set_mode((width, height + 100))

# Change the screen caption
pg.display.set_caption('Tic Tac Toe')

clock = pg.time.Clock()

#tree = Minmax('O')


# -------------------------- Define Functions --------------------------
def draw_board():
    # change the screen colour
    screen.fill(white)

    # draw vertical board lines
    pg.draw.line(screen, black, (width / 3, 0), (width / 3, height), 7)
    pg.draw.line(screen, black, (width / 3 * 2, 0), (width / 3 * 2, height), 7)

    # draw horizontal board lines
    pg.draw.line(screen, black, (0, height / 3), (width, height / 3), 7)
    pg.draw.line(screen, black, (0, height / 3 * 2), (width, height / 3 * 2), 7)
    draw_status()


def draw_status():
    # Check current game status
    if winner is None:
        message = XO.upper() + "'s Turn"
    else:
        message = winner.upper() + " won !"
    if draw:
        message = "Game Draw !"

    # Create font object
    font = pg.font.Font(None, 30)

    # Create text object
    text = font.render(message, 1, (255, 255, 255))

    # Display current game status
    screen.fill(black, (0, 400, 500, 100))
    text_rect = text.get_rect(center=(width / 2, 500 - 50))
    screen.blit(text, text_rect)
    pg.display.update()


def check_win():
    global board, winner, draw

    # checking for winning rows
    for row in range(0, 3):
        if (board[row][0] == board[row][1] == board[row][2]) and (board[row][0] is not None):
            winner = board[row][0]
            pg.draw.line(screen, (250, 0, 0),
                         (0, (row + 1) * height / 3 - height / 6),
                         (width, (row + 1) * height / 3 - height / 6),
                         4)
            break

    # checking for winning columns
    for col in range(0, 3):
        if (board[0][col] == board[1][col] == board[2][col]) and (board[0][col] is not None):
            winner = board[0][col]
            pg.draw.line(screen, (250, 0, 0), ((col + 1) * width / 3 - width / 6, 0), \
                         ((col + 1) * width / 3 - width / 6, height), 4)
            break

    # check for diagonal winners
    if (board[0][0] == board[1][1] == board[2][2]) and (board[0][0] is not None):
        # game won diagonally left to right
        winner = board[0][0]
        pg.draw.line(screen, (250, 70, 70), (50, 50), (350, 350), 4)

    if (board[0][2] == board[1][1] == board[2][0]) and (board[0][2] is not None):
        # game won diagonally right to left
        winner = board[0][2]
        pg.draw.line(screen, (250, 70, 70), (350, 50), (50, 350), 4)

    if all([all(row) for row in board]) and winner is None:
        draw = True
    draw_status()


def draw_xo(row, col):
    global board, XO

    # Check which row to draw the symbol
    if row == 0:
        x = 30
    elif row == 1:
        x = width / 3 + 30
    else:
        x = width / 3 * 2 + 30

    # Check which column to draw the symbol
    if col == 0:
        y = 30
    elif col == 1:
        y = height / 3 + 30
    else:
        y = height / 3 * 2 + 30

    # setting up the required board
    # value to display
    board[row][col] = XO

    # Draw the symbol
    # Switch to next player
    if XO == 'X':
        screen.blit(x_img, (y, x))
        XO = 'O'
    else:
        screen.blit(o_img, (y, x))
        XO = 'X'
    pg.display.update()


def user_click():
    global board, draw
    # get coordinates of mouse click
    x, y = pg.mouse.get_pos()

    # get column of mouse click (1-3)
    if x < width / 3:
        col = 0
    elif x < width / 3 * 2:
        col = 1
    elif x < width:
        col = 2
    else:
        col = None

    # get row of mouse click (1-3)
    if y < height / 3:
        row = 0
    elif y < height / 3 * 2:
        row = 1
    elif y < height:
        row = 2
    else:
        row = None

    # after getting the row and col,
    # we need to draw the images at
    # the desired positions
    if row is not None and col is not None and board[row][col] is None:
        draw_xo(row, col)
        check_win()


def reset_game():
    global board, winner, XO, draw
    time.sleep(3)
    XO = 'X'
    draw = False
    draw_board()
    winner = None
    board = [[None] * 3, [None] * 3, [None] * 3]


# -------------------------- Main game loop --------------------------
draw_board()

while not done:
    for event in pg.event.get():
        if event.type == pg.QUIT:
            done = True
        elif event.type == pg.MOUSEBUTTONDOWN:
            user_click()
            if winner or draw:
                reset_game()
    pg.display.update()
    clock.tick(30)
