### NeoPixel Pendant/Trinket by Pixel 2018
 
import time
import board
import neopixel
import math
import storage

try:
    import urandom as random  # for v1.0 API support
except ImportError:
    import random

#strip setup
pixpin = board.D0
num_leds = 8

BPP=4

ledBright = 0.07

f = open("/data.txt", "r")
line = f.readline()
f.close()
savedMode=int(line)

try:
    f = open("data.txt", "w")
    if savedMode == 2:
        f.write("0")
        ledBright = 1
    elif savedMode == 1:
        f.write("2")
        ledBright = 0.2
    else:
        f.write("1")
        ledBright = 0.08       
    f.close()
except:
    if savedMode == 2:
        ledBright = 1
    elif savedMode == 1:
        ledBright = 0.3
    else:
        ledBright = 0.01

pixels = neopixel.NeoPixel(pixpin, num_leds, brightness=ledBright, auto_write=False)
#Demos to run
theater = 1
colorWipe = 1
runLight = 0
cylon = 1
sparkles = 0
firePlace = 0

# Constants
RED = (255, 0, 0)
DARKRED = (70, 0, 0)
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

def sparklesDemo(color, wait,iterate):
    for i in range(iterate):
        pixel = random.randint(0, num_leds-1)
        colorbool = random.randint(0, 1)       
        if colorbool == 1:
            colorNOW = color
        else:
            colorNOW = BLACK
        pixels[pixel] = colorNOW
        pixels.write()
        time.sleep(wait)

def shiftList(list, amount):
        return list[amount:] + list[:amount]

def wheel(pos):
    if pos < 85:
        return (int(pos * 3), int(255 - (pos * 3)), 0)
    elif pos < 170:
        pos -= 85
        return (int(255 - (pos * 3)), 0, int(pos * 3))
    else:
        pos -= 170
        return (0, int(pos * 3), int(255 - pos * 3))

def intpow(e,n):
  v = 1
  for x in range (0,n):
    v *= e
  return v

def swirl_colour(start, pix):
    off = (pix - start) & 0x0F
    if(off < 4):
        amt = intpow(2, off+1)
        green = (0, amt,0)
        return green
    else:
        return BLACK

def loop_swirl(loopy, SpeedDelay):
  for i in range(loopy):
    for y in range(5):
        for led in range(8):
            pixels[led] = swirl_colour(y, led)
        pixels.show()
        time.sleep(SpeedDelay)

def cylonDemo(color, EyeSize, SpeedDelay, ReturnDelay, iterate):
    for i in range (iterate):
        for i in range(num_leds-EyeSize-1):
            setAll(0,0,0)
            pixels[i] = color
            for j in range(EyeSize+1):
                pixels[i+j] = color
            pixels[i+EyeSize+1] = color
            pixels.show()
        time.sleep(SpeedDelay)

        time.sleep(ReturnDelay)

        for i in range(num_leds-EyeSize-2,-1,-1):
            setAll(0,0,0)
            pixels[i] = color
            for j in range(0,EyeSize+1):
                pixels[i+j] = color
            pixels[i+EyeSize+1] = color
            pixels.show()
        time.sleep(SpeedDelay)

        time.sleep(ReturnDelay)

def colorWipeDemo(color, SpeedDelay, iterate):
    for i in range(iterate):
        for i in range(num_leds):
            pixels[i] = color
            pixels.show()
            time.sleep(SpeedDelay)

def theaterDemo(color, SpeedDelay, iterate):
    for i in range(iterate):
        for q in range(2):
            for i in range(0,num_leds,2):
                pixels[i+q] = color
            pixels.show()
            time.sleep(SpeedDelay)
            for i in range(0,num_leds,2):
                pixels[i+q] = BLACK

def setAll(red, green, blue):
  for i in range(num_leds):
    pixels[i] = (red, green, blue)
  pixels.show()

colorsList = [RED,YELLOW,ORANGE,GREEN,TEAL,CYAN,BLUE,PURPLE,MAGENTA,WHITE]
lastColor = 0
colorNow = 0

lastMode = 0
mode = 5
lastSpd = 0
spd = 0
while True:
    while spd == lastSpd:
        spd = random.uniform(0.01, 0.08)
    lastSpd = spd
    while colorNow == lastColor:
        colorNow = random.randint(0, len(colorsList)-1)
    lastColor = colorNow
    #while mode == lastMode:
        #mode = random.randint(0,4)
    #lastMode = mode
   # for i in range(len(colorsList)):
    colorDemos = colorsList[colorNow]
    if mode == 5:
        loop_swirl(100, spd)

    if mode == 4:
            theaterDemo(colorDemos,spd,11)

    if mode == 3:
        for i in range(5):
            colorWipeDemo(colorDemos,spd,1)
            colorWipeDemo(BLACK,spd,1)

    if mode == 2:
            pixels.show()

    if mode == 1:
            cylonDemo(colorDemos, 1, spd, spd,10)
        
    if mode == 0:
        sparklesDemo(colorDemos, spd,300)
