# CircuitPython demo - NeoPixel
 
import time
 
import board
import neopixel
 
pixpin = board.D0
numpix = 19
 
pixels = neopixel.NeoPixel(pixpin, numpix, brightness=0.6, auto_write=False)
 
wait = 1
simpleCircleDemo = 1
flashDemo = 1
rainbowDemo = 1
rainbowCycleDemo = 1
burningMan = 1

def burningMan():
   pixels[0] = ((255, 0, 0))
   pixels[1] = ((255, 255, 0))
   pixels[2] = ((255, 0, 0))
   pixels[3] = ((255, 255, 0))
   pixels[4] = ((255, 255, 0))
   pixels[5] = ((255, 0, 0))
   pixels[6] = ((255, 255, 0))
   pixels[7] = ((255, 255, 0))
   pixels[8] = ((255, 255, 0))
   pixels[9] = ((255, 255, 0))
   pixels[10] = ((255, 0, 0))
   pixels[11] = ((255, 0, 0))
   pixels[12] = ((255, 0, 0))
   pixels[13] = ((255, 255, 0))
   pixels[14] = ((255, 0, 0))
   pixels[15] = ((255, 255, 0))
   pixels[16] = ((255, 0, 0))
   pixels[17] = ((255, 0, 0))
   pixels[18] = ((255, 0, 0))
   pixels.write()
   time.sleep(2)
   pixels[0] = ((0, 0, 255))
   pixels[1] = ((255, 255, 0))
   pixels[2] = ((0, 0, 255))
   pixels[3] = ((255, 255, 0))
   pixels[4] = ((255, 255, 0))
   pixels[5] = ((0, 0, 255))
   pixels[6] = ((255, 255, 0))
   pixels[7] = ((255, 255, 0))
   pixels[8] = ((255, 255, 0))
   pixels[9] = ((255, 255, 0))
   pixels[10] = ((0, 0, 255))
   pixels[11] = ((0, 0, 255))
   pixels[12] = ((0, 0, 255))
   pixels[13] = ((255, 255, 0))
   pixels[14] = ((0, 0, 255))
   pixels[15] = ((255, 255, 0))
   pixels[16] = ((0, 0, 255))
   pixels[17] = ((0, 0, 255))
   pixels[18] = ((0, 0, 255))
   pixels.write()
   time.sleep(2)
 

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
    RED = (255, 0, 0)  # (0x10, 0, 0) also works
    YELLOW = (255, 255, 0)
    GREEN = (0, 255, 0)
    AQUA = (0, 255, 255)
    BLUE = (0, 0, 255)
    PURPLE = (255, 0, 255)
    BLACK = (0, 0, 0)
 
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
 
 
 
while True:
    if burningMan:
        burningMan()

   # if simpleCircleDemo:
    #    simpleCircle(1)
 
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