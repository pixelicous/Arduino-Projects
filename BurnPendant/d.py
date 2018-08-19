import time
import board
import neopixel
import storage

try:
    import urandom as random  # for v1.0 API support
except ImportError:
    import random

RED = (255, 0, 0)
YELLOW = (255, 150, 0)
DYELLOW = (150, 150, 0)
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

f = open("/data.txt", "r")
line = f.readline()
f.close()
savedMode=int(line)

f = open("data.txt", "w")
if (savedMode == 1):
    f.write("0")
    ledBright = 1
else:
    f.write("1")
    ledBright = 0.07
f.close()

#f = open("data.txt", "w")
if (savedMode == 1):
    #f.write(int(0))
    ledBright = 0.8
else:
    #f.write(int(1))
    ledBright = 0.05

#strip setup
pixpin = board.D0
num_leds = 19

pixels = neopixel.NeoPixel(pixpin, num_leds, brightness=ledBright, auto_write=False)


def flowerDemo(wait,colorOne,colorTwo,colorThree):
    pixels[0] = colorThree
    for i in range(1,7):
        pixels[i] = colorOne  
    for i in range(7,19):
        pixels[i] = colorTwo
    pixels.write()
    time.sleep(wait)


def burningManRollDemo(wait,colorOne,colorTwo):
    colorListJewel = [colorTwo,colorOne,colorTwo,colorTwo,colorOne,colorTwo]
    colorListRing = [colorTwo,colorTwo,colorTwo,colorOne,colorOne,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorOne,colorOne]

    pixels[0] = colorTwo
    for y in range(6):
        for i in range(len(colorListJewel)):
            tempColorList = shiftList(colorListJewel,y)
            pixels[i+1] = tempColorList[i]
    

        for i in range(len(colorListRing)):
            tempColorList = shiftList(colorListRing,y*2)
            pixels[i+7] = tempColorList[i]
        pixels.write()
        time.sleep(wait)

def shiftList(list, amount):
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

def whiteSparklesDemo(wait,iterate):
    for i in range(iterate):
        pixel = random.randint(0, num_leds-1)
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
        pixel = random.randint(0, num_leds-1)
        color = random.randint(0, len(colorsList)-1) 
        pixels[pixel] = sparks_colorsList[color]
        pixels.write()
        time.sleep(wait)

def firePlaceDemo(wait,iterate):
    for i in range(iterate):
        pixel = random.randint(0, num_leds-1)
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
 
def cylonDemo(color, EyeSize, SpeedDelay, ReturnDelay, iterate):
    for i in range (iterate):
        for i in range(num_leds-EyeSize-1):
            setAll(BLACK)
            pixels[i] = color
            for j in range(EyeSize+1):
                pixels[i+j] = color
            pixels[i+EyeSize+1] = color
            pixels.show()
        time.sleep(SpeedDelay)

        time.sleep(ReturnDelay)

        for i in range(num_leds-EyeSize-2,-1,-1):
            setAll(BLACK)
            pixels[i] = color
            for j in range(0,EyeSize+1):
                pixels[i+j] = color
            pixels[i+EyeSize+1] = color
            pixels.show()
        time.sleep(SpeedDelay)

        time.sleep(ReturnDelay)

def playaDemo(wait,One,Two):
    ListJewel = [One,One,One,One,One,One,Two,Two,Two,One,Two,One,Two,One,Two,One,Two,One,Two]

    for i in range(len(ListJewel)):
        pixels[i] = ListJewel[i]
    pixels.write()
    time.sleep(wait)

def rotateDemo(wait,colorOne,colorTwo):
    colorListJewel = [colorOne,colorTwo,colorOne,colorOne,colorTwo,colorOne]
    colorListRing = [colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo]

    pixels[0] = colorTwo
    for y in range(6):
        for i in range(len(colorListJewel)):
            tempColorList = shiftList(colorListJewel,y)
            pixels[i+1] = tempColorList[i]


        for i in range(len(colorListRing)):
            tempColorList = shiftList(colorListRing,y*3)
            pixels[i+7] = tempColorList[i]
        pixels.write()
        time.sleep(wait)

def setAll(color):
  for i in range(num_leds):
    pixels[i] = color
  pixels.show()

def colorWipeDemo(color, SpeedDelay, iterate):
    for i in range(iterate):
        for i in range(num_leds):
            pixels[i] = color
            pixels.show()
            time.sleep(SpeedDelay)