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
pixels = neopixel.NeoPixel(pixpin, num_pixels, brightness=0.01, auto_write=False)

#Demos to run
sparks = 1


#add sets of demos
#use bootrom to jump between sets
#have a set with all demos
#add a demo that does outer ring circle then inner, can go out and in- in same function
# Constants
RED = (255, 0, 0)
YELLOW = (255, 150, 0)
ORANGE = (255, 40, 0)
GREEN = (0, 255, 0)
TEAL = (0, 255, 120)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
MAGENTA = (255, 0, 20)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

colorsList = [RED,YELLOW,ORANGE,GREEN,TEAL,CYAN,BLUE,PURPLE,MAGENTA,WHITE]

while True:
    for i in range(0,num_pixels):
        pixels[i] = GREEN
        pixels.write()
        time.sleep(0.4)
    for i in range(0,num_pixels):
        pixels[i] = BLUE
        pixels.write()
        time.sleep(0.4)