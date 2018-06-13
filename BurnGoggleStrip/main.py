### NeoPixel Pendant/Trinket by Pixel 2018
 
import time
import board
import neopixel

try:
    import urandom as random  # for v1.0 API support
except ImportError:
    import random

#strip setup
pixpin = board.D0
num_pixels = 8

BPP=4

pixels = neopixel.NeoPixel(pixpin, num_pixels, bpp=BPP, brightness=0.01, auto_write=False)

#Demos to run
sparks = 1
whiteSparkles = 1
firePlace = 1
rainbowDemo = 1
rainbowCycleDemo = 1

# Constants
RED = (255, 0, 0, 0)
YELLOW = (255, 150, 0, 0)
ORANGE = (255, 40, 0, 0)
GREEN = (0, 255, 0, 0)
TEAL = (0, 255, 120, 0)
CYAN = (0, 255, 255, 0)
BLUE = (0, 0, 255, 255, 0)
PURPLE = (180, 0, 255, 0)
MAGENTA = (255, 0, 20, 0)
WHITE = (255, 255, 255, 0)
BLACK = (0, 0, 0, 0)

colorsList = [RED,YELLOW,ORANGE,GREEN,TEAL,CYAN,BLUE,PURPLE,MAGENTA,WHITE]

def whiteSparklesDemo(wait,iterate):
    for i in range(iterate):
        pixel = random.randint(0, num_pixels-1)
        colorbool = random.randint(0, 1)       
        if colorbool == 1:
            color = WHITE
        else:
            color = BLACK
        pixels[pixel] = color
        pixels.write()
        time.sleep(wait)

def sparksDemo(wait,iterate):
    for i in range(iterate):
        sparks_colorsList = [RED,YELLOW,BLACK,ORANGE,GREEN,TEAL,BLACK,CYAN,BLACK,BLUE,PURPLE,MAGENTA,WHITE,BLACK]
        pixel = random.randint(0, num_pixels-1)
        color = random.randint(0, len(colorsList)-1) 
        pixels[pixel] = sparks_colorsList[color]
        pixels.write()
        time.sleep(wait)

def firePlaceDemo(wait,iterate):
    for i in range(iterate):
        pixel = random.randint(0, num_pixels-1)
        color = (random.randint(50, 255), random.randint(0, 40), 0)
        pixels[pixel] = color
        pixels.write()
        time.sleep(wait)

 
def rainbow_cycle(wait):
    for j in range(255):
        for i in range(len(pixels)):
            idx = int((i * 256 / len(pixels)) + j * 10)
            pixels[i] = wheel(idx & 255)
        pixels.show()
        time.sleep(wait)
 
 
def rainbow(wait):
    for j in range(255):
        for i in range(len(pixels)):
            idx = int(i + j)
            pixels[i] = wheel(idx & 255)
        pixels.show()
        time.sleep(wait)


def firePlaceDemo(wait,iterate):
    for i in range(iterate):
        pixel = random.randint(0, num_pixels-1)
        color = (random.randint(50, 255), random.randint(0, 40), 0)
        pixels[pixel] = color
        pixels.write()
        time.sleep(wait)

def shiftList(list, amount):
        return list[amount:] + list[:amount]

def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if pos < 85:
        return (int(pos * 3), int(255 - (pos * 3)), 0, 0)
    elif pos < 170:
        pos -= 85
        return (int(255 - (pos * 3)), 0, int(pos * 3), 0)
    else:
        pos -= 170
        return (0, int(pos * 3), int(255 - pos * 3), 0)

while True:

    if whiteSparkles:
        whiteSparklesDemo(0.001,300)

    if sparks:
        sparksDemo(0.01,300)

    if firePlace:
        firePlaceDemo(0.01,300)

    if rainbowDemo:
        for i in range(3):
            rainbow(.002)
 
    if rainbowCycleDemo:
        for i in range(3):
            rainbow_cycle(.002)

