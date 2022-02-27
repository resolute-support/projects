import pygame as pg
import os
import time
import random

pg.init()

# ---------------------------- Variable Definitions ----------------------------
# Define screen dimensions
width = 600
height = 600

# Define colours 
white = (255, 255, 255)
black = (0, 0, 0)
red = (250, 0, 0)
 
# Define flags
done = False
game_over = False
startup = True

# Define game variables
snake_size = 10
snake_speed = 7
x1 = width / 2
y1 = height / 2

x1_change = 0
y1_change = 0

snake = []
snake_len = 1

foodx = round(random.randrange(0, width - snake_size) / 10.0) * 10.0
foody = round(random.randrange(0, height - snake_size) / 10.0) * 10.0

# Import assets
path = os.path.dirname(__file__)
assets = os.path.join(path, 'assets')
background = pg.image.load(os.path.join(assets, 'grass.png'))

# Create game screen
screen = pg.display.set_mode((width, height))
pg.display.set_caption('Snake')
 
# Create clock to control screen refresh rate
clock = pg.time.Clock()
 
# Set game fonts
font_style = pg.font.SysFont("bahnschrift", 25)
score_font = pg.font.SysFont("bahnschrift", 25)


# ---------------------------- Function Definitions ----------------------------
# Draw the screen background
def draw_screen():
    screen.blit(background, (0, 0))


# Draw the player's score
def draw_score(score):
    value = score_font.render("Your Score: " + str(score), True, white)
    screen.blit(value, [0, 0])
 
 
#  Draw the snake
def draw_snake(snake_size, snake):
    for x in snake:
        pg.draw.rect(screen, black, [x[0], x[1], snake_size, snake_size])


# Draw the food
def draw_food(screen, size, x, y):
    pg.draw.rect(screen, red, [x, y, size, size])
 
 
#  Display game over message
def display_message(msg, color):
    mesg = font_style.render(msg, True, color)
    mesg_rect = mesg.get_rect(center=(width/2, height/2))
    screen.blit(mesg, mesg_rect)


# Reset games state
def reset():
    global snake_size, snake_speed, x1, y1, x1_change, y1_change, snake, snake_len, foodx, foody
    # Set snake starting coordinates
    x1 = width / 2
    y1 = height / 2

    # Reset snake velocity
    x1_change = 0
    y1_change = 0

    # Reset snake length
    snake = []
    snake_len = 1

    # Reset food coordinates
    foodx = round(random.randrange(0, width - snake_size) / 10.0) * 10.0
    foody = round(random.randrange(0, height - snake_size) / 10.0) * 10.0
 

# ---------------------------- Game Loop ----------------------------
while not done:

    while startup == True:
        screen.fill(black)
        display_message("Welcome to Snake! Press any key to continue", white)
        pg.display.update()

        for event in pg.event.get():
            if event.type == pg.KEYDOWN: 
                    reset()
                    startup = False

    for event in pg.event.get():
        if event.type == pg.QUIT:
            done = True
        if event.type == pg.KEYDOWN:
            if event.key == pg.K_LEFT and x1_change == 0:
                x1_change = -snake_size
                y1_change = 0
            elif event.key == pg.K_RIGHT and x1_change == 0:
                x1_change = snake_size
                y1_change = 0
            elif event.key == pg.K_UP and y1_change == 0:
                y1_change = -snake_size
                x1_change = 0
            elif event.key == pg.K_DOWN and y1_change == 0:
                y1_change = snake_size
                x1_change = 0

    if x1 >= width or x1 < 0 or y1 >= height or y1 < 0:
        game_over = True

    x1 += x1_change
    y1 += y1_change
    draw_screen()

    draw_food(screen, snake_size, foodx, foody)
    head = []
    head.append(x1)
    head.append(y1)
    snake.append(head)

    if len(snake) > snake_len:
        del snake[0]

    for x in snake[:-1]:
        if x == head:
            game_over = True

    draw_snake(snake_size, snake)
    draw_score(snake_len - 1)

    pg.display.update()

    if x1 == foodx and y1 == foody:
        foodx = round(random.randrange(0, width - snake_size) / 10.0) * 10.0
        foody = round(random.randrange(0, height - snake_size) / 10.0) * 10.0
        snake_len += 1

    clock.tick(snake_speed)

    while game_over == True:
        screen.fill(black)
        display_message("You Lost! Press C to play again", white)
        draw_score(snake_len - 1)
        pg.display.update()

        for event in pg.event.get():
            if event.type == pg.KEYDOWN: 
                if event.key == pg.K_c:
                    reset()
                    game_over = False
            elif event.type == pg.QUIT:
                done = True
                startup = True
                game_over = False
