# CircuitPython demo - NeoPixel
 
import time
 
import board
import neopixel
 
pixpin = board.D0
num_pixels = 19
 
pixels = neopixel.NeoPixel(pixpin, num_pixels, brightness=0.3, auto_write=False)
 
simpleCircleDemo = 0
flashDemo = 1
rainbowDemo = 1
rainbowCycleDemo = 1
burningMan = 0
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

def burningManDemo(wait,iterate):
    for i in range(0,30):
        pixels[0] = RED
        pixels[1] = ((255, 255, 0))
        pixels[2] = RED
        pixels[3] = ((255, 255, 0))
        pixels[4] = ((255, 255, 0))
        pixels[5] = RED
        pixels[6] = ((255, 255, 0))
        pixels[7] = ((255, 255, 0))
        pixels[8] = ((255, 255, 0))
        pixels[9] = ((255, 255, 0))
        pixels[10] = RED
        pixels[11] = RED
        pixels[12] = RED
        pixels[13] = ((255, 255, 0))
        pixels[14] = RED
        pixels[15] = ((255, 255, 0))
        pixels[16] = RED
        pixels[17] = RED
        pixels[18] = RED
        pixels.write()
        time.sleep(wait)
        pixels[0] = BLUE
        pixels[1] = ((255, 255, 0))
        pixels[2] = BLUE
        pixels[3] = ((255, 255, 0))
        pixels[4] = ((255, 255, 0))
        pixels[5] = BLUE
        pixels[6] = ((255, 255, 0))
        pixels[7] = ((255, 255, 0))
        pixels[8] = ((255, 255, 0))
        pixels[9] = ((255, 255, 0))
        pixels[10] = BLUE
        pixels[11] = BLUE
        pixels[12] = BLUE
        pixels[13] = ((255, 255, 0))
        pixels[14] = BLUE
        pixels[15] = ((255, 255, 0))
        pixels[16] = BLUE
        pixels[17] = BLUE
        pixels[18] = BLUE
        pixels.write()
        time.sleep(wait)
 

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
 
 
while True:
    if burningMan:
        burningManDemo(0.1,10)

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

