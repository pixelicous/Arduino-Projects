# CircuitPython demo - NeoPixel
 
import time
 
import board
import neopixel
 
try:
    import urandom as random  # for v1.0 API support
except ImportError:
    import random

pixpin = board.D0
num_pixels = 19
 
pixels = neopixel.NeoPixel(pixpin, num_pixels, brightness=0.2, auto_write=False)
lastPixel = 0
pixel = 1
simpleCircleDemo = 0
sparks = 0
firePlace = 1
flashDemo = 0
rainbowDemo = 0
rainbowCycleDemo = 0
burningManRoll = 0
sliceAlternating = 0

RED = (255, 0, 0)
YELLOW = (255, 150, 0)
ORANGE = (255, 40, 0)
GREEN = (0, 255, 0)
TEAL = (0, 255, 120)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
AQUA = (0, 255, 255)
PURPLE = (180, 0, 255)
MAGENTA = (255, 0, 20)
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)

colors_list = [RED,YELLOW,BLACK,ORANGE,GREEN,TEAL,BLACK,CYAN,BLACK,BLUE,AQUA,PURPLE,MAGENTA,WHITE,BLACK]

def sparksDemo(wait,iterate):
     #  while pixel == lastPixel :
        pixel = random.randint(0, num_pixels-1)
        color = random.randint(0, len(colors_list)-1) 
        pixels[pixel] = colors_list[color]
        pixels.write()
        time.sleep(wait)
        lastPixel = pixel

def firePlaceDemo(wait,iterate):
     #  while pixel == lastPixel :
    pixel = random.randint(0, num_pixels-1)
    color = (random.randint(50, 255), random.randint(0, 40), 0)
    pixels[pixel] = color
    pixels.write()
    time.sleep(wait)
    lastPixel = pixel

def burningManRollDemo(wait,iterate,colorOne,colorTwo):
    colorListJewel = [colorTwo,colorOne,colorTwo,colorTwo,colorOne,colorTwo]
    colorListRing = [colorTwo,colorTwo,colorTwo,colorOne,colorOne,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorOne,colorOne]

    pixels[0] = colorTwo
    for y in range(6):
        for i in range(len(colorListJewel)):
            tempColorList = shift_list(colorListJewel,y)
            pixels[i+1] = tempColorList[i]
    

        for i in range(len(colorListRing)):
            tempColorList = shift_list(colorListRing,y*2)
            pixels[i+7] = tempColorList[i]
        pixels.write()
        time.sleep(wait)
        

def shift_list(list, amount):
        return list[amount:] + list[:amount]

def wheel(pos):
    # Input a value 0 to 255 to get a color value.
    # The colours are a transition r - g - b - back to r.
    if pos < 85:
        return (int(pos * 3), int(255 - (pos * 3)), 0)
    elif pos < 170:
        pos -= 85
        return (int(255 - (pos * 3)), 0, int(pos * 3))
    else:
        pos -= 170
        return (0, int(pos * 3), int(255 - pos * 3))
 
 
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
 
 
def simpleCircle(wait):

    for i in range(len(pixels)):
        pixels[i] = RED
        time.sleep(wait)
    time.sleep(1)
 
    for i in range(len(pixels)):
        pixels[i] = YELLOW
        time.sleep(wait)
    time.sleep(1)
 
    for i in range(len(pixels)):
        pixels[i] = GREEN
        time.sleep(wait)
    time.sleep(1)
 
    for i in range(len(pixels)):
        pixels[i] = AQUA
        time.sleep(wait)
    time.sleep(1)
 
    for i in range(len(pixels)):
        pixels[i] = BLUE
        time.sleep(wait)
    time.sleep(1)
 
    for i in range(len(pixels)):
        pixels[i] = PURPLE
        time.sleep(wait)
    time.sleep(1)
 
    for i in range(len(pixels)):
        pixels[i] = BLACK
        time.sleep(wait)
    time.sleep(1)
 
#NOT ACTIVE
def slice_alternating(wait):
    pixels[::2] = [RED] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[1::2] = [ORANGE] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[::2] = [YELLOW] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[1::2] = [GREEN] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[::2] = [TEAL] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[1::2] = [CYAN] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[::2] = [BLUE] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[1::2] = [PURPLE] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[::2] = [MAGENTA] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
    pixels[1::2] = [WHITE] * (num_pixels // 2)
    pixels.show()
    time.sleep(wait)
 
### MAIN LOOP

while True:
    if burningManRoll:
        for i in range(len(colors_list)-1):
            burningManRollDemo(0.7,10,colors_list[i],colors_list[i+1])
    
    if sparks:
        sparksDemo(0.03,10)

    if firePlace:
        firePlaceDemo(0.03,10)

    if sliceAlternating:
        slice_alternating(3)
   
    if simpleCircleDemo:
        simpleCircle(1)
 
    if flashDemo:  # this will play if flashDemo = 1 up above
        pixels.fill((255, 0, 0))
        pixels.show()
        time.sleep(.25)
 
        pixels.fill((0, 255, 0))
        pixels.show()
        time.sleep(.25)
 
        pixels.fill((0, 0, 255))
        pixels.show()
        time.sleep(.25)
 
        pixels.fill((255, 255, 255))
        pixels.show()
        time.sleep(.25)
 
    if rainbowDemo:
        for i in range(3):
            rainbow(.002)
 
    if rainbowCycleDemo:
        for i in range(3):
            rainbow_cycle(.002)

