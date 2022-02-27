import pygame as pg
import os

pg.init()

# Define constants
black = (0, 0, 0)
red = (254, 52, 110)
green = (0, 255, 0)
white = (255, 255, 255)
width = 667
height = 667

# Import assets
path = os.path.dirname(__file__)
assets = os.path.join(path, "assets")
background = pg.image.load(os.path.join(assets, 'background.png'))
alien = pg.image.load(os.path.join(assets, 'alien.png'))
ship = pg.image.load(os.path.join(assets, 'ship.png'))

alien = pg.transform.scale(alien, (50, 50))
ship = pg.transform.scale(ship, (50, 50))


class Game:
    clock = None

    def __init__(self, width, height):
        # Initialize game variables
        self.game_over = False
        self.done = False
        self.clock = pg.time.Clock()
        self.hero = None
        self.aliens = None
        self.rockets = None
        self.sprites = None

        # Define screen dimensions
        self.width = width
        self.height = height

        # Create screen
        self.screen = pg.display.set_mode((width, height))
        pg.display.set_caption('Space Invaders')

        self.reset()

        while not self.done:
            # Check if player has won
            if len(self.aliens.sprites()) == 0:
                self.display_text('WINNER!')

            # Get player input (left/right)
            pressed = pg.key.get_pressed()
            if pressed[pg.K_LEFT]:
                if self.hero.rect.left > 0:
                    self.hero.x -= 2
                else:
                    self.hero.x -= 0
            elif pressed[pg.K_RIGHT]:
                if self.hero.rect.right < self.width:
                    self.hero.x += 2
                else:
                    self.hero.x += 0

            # Get player input (quit/fire rockets)
            for event in pg.event.get():
                if event.type == pg.QUIT:
                    self.done = True
                if event.type == pg.KEYDOWN and event.key == pg.K_SPACE and not self.game_over:
                    rocket = Rocket(self.hero.rect.center[0], self.hero.rect.top)
                    self.rockets.add(rocket)
                    self.sprites.add(rocket)

            pg.display.update()
            self.clock.tick(60)

            self.screen.blit(background, (0, 0))

            if not self.game_over:
                # Update all sprite positionss
                self.sprites.update()

                # Draw all sprites
                self.sprites.draw(self.screen)

                # Check for collisions
                collisions = pg.sprite.groupcollide(self.aliens, self.rockets, True, True)

                collisions = pg.sprite.spritecollide(self.hero, self.aliens, False)
                if len(collisions) > 0:
                    self.game_over = True

                for alien in self.aliens:
                    if alien.rect.bottom == self.height:
                        self.game_over = True

            #  Game over loop
            while self.game_over:
                self.screen.fill(black)
                self.display_text('Game Over (Press C)')
                pg.display.update()

                for event in pg.event.get():
                    if event.type == pg.KEYDOWN:
                        if event.key == pg.K_c:
                            self.reset()
                            self.game_over = False
                    elif event.type == pg.QUIT:
                        self.done = True
                        self.game_over = False

    def reset(self):
        # Create sprite groups
        self.sprites = pg.sprite.Group()
        self.rockets = pg.sprite.Group()
        self.aliens = pg.sprite.Group()

        # Create alien sprites
        self.generator = Generator(self)

        # Create hero sprite
        self.hero = Hero(width / 2, height - 60)
        self.sprites.add(self.hero)

    def display_text(self, text):
        pg.font.init()
        font = pg.font.Font(None, 50)
        textsurface = font.render(text, False, white)
        text_rect = textsurface.get_rect(center=(width/2, height/2))
        self.screen.blit(textsurface, text_rect)


class Alien(pg.sprite.Sprite):
    def __init__(self, x, y):
        pg.sprite.Sprite.__init__(self)
        self.image = alien
        self.x = x
        self.y = y
        self.rect = self.image.get_rect(center=(x, y))

    def update(self):
        self.y += 0.15
        self.rect.y = self.y


class Hero(pg.sprite.Sprite):
    def __init__(self, x, y):
        pg.sprite.Sprite.__init__(self)
        self.image = ship
        self.x = x
        self.y = y
        self.rect = self.image.get_rect(center=(x, y))

    def update(self):
        self.rect.x = self.x


class Rocket(pg.sprite.Sprite):
    def __init__(self, x, y):
        pg.sprite.Sprite.__init__(self)
        self.image = pg.Surface((4, 8))
        self.image.fill(red)
        self.x = x
        self.y = y
        self.rect = self.image.get_rect(center=(x, y))

    def update(self):
        self.y -= 2
        self.rect.y = self.y


class Generator:
    def __init__(self, game):
        margin = 50
        width = 70
        for x in range(margin, game.width - margin, width):
            for y in range(margin, int(game.height / 2), width):
                alien = Alien(x, y)
                game.aliens.add(alien)
                game.sprites.add(alien)


game = Game(width, height)
