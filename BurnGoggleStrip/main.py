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

ledBright = 5

#f = open("/data.txt", "r")
#line = f.readline()
#f.close()
#savedMode=int(line)

#f = open("data.txt", "w")
#if (savedMode == 1):
#    f.write(int(0))
#    ledBright = 10
#else:
#    f.write(int(1))
#    ledBright = 0.07

#f.write("\n")
#f.close()

pixels = neopixel.NeoPixel(pixpin, num_leds, brightness=ledBright, auto_write=False)
#Demos to run
theater = 1
colorWipe = 1
runLight = 0
cylon = 1
knightrider = 0
sparks = 1
whiteSparkles = 1
firePlace = 1
rainbow = 1
rainbowCycleDemo = 0

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

def knightriderDemo():
    for i in range(iterate):
        for i in range(num_leds):
            pixels[i] = DARKRED 
        pixels.show()
        time.sleep(0.9)
        for i in range(num_leds/2):
            pixels[i] = RED
            pixels[num_leds-i-1] = RED
            time.sleep(0.03)
            pixels.show()
        for i in range(num_leds/2):
            pixels[i] = CYAN
            pixels[num_leds-i-1] = PURPLE
            time.sleep(0.3)
            pixels.show()
        for i in range(num_leds/2):
            pixels[i] = GREEN
            pixels[num_leds-i-1] = BLUE
            time.sleep(0.3)
            pixels.show()
        pixels.show()

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
 
 
def rainbowDemo(wait):
    for j in range(255):
        for i in range(len(pixels)):
            idx = int(i + j)
            pixels[i] = wheel(idx & 255)
        pixels.show()
        #time.sleep(wait)

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

def RunningLights(red, green, blue, WaveDelay, iterate):
  Position=0
  
  for i in range (num_leds*2):
      Position += 1
      for i in range(num_leds):
          #pixels[i] = (255,0,0)
          pixels[i] = ((math.sin(i+Position) * 127 + 128)/255)*red,((math.sin(i+Position) * 127 + 128)/255)*green,((math.sin(i+Position) * 127 + 128)/255)*blue
      pixels.show()
      time.sleep(WaveDelay)

def colorWipeDemo(color, SpeedDelay, iterate):
    for i in range(iterate):
        for i in range(num_leds):
            pixels[i] = color
            pixels.show()
            time.sleep(SpeedDelay)

def theaterDemo(color, SpeedDelay, iterate):
    for i in range(iterate):
        for j in range(2):
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

while True:
        if theater:
                theaterDemo(YELLOW,0.06,11)

        if colorWipe:
            for i in range(5):
                colorWipeDemo(BLUE,0.02,1)
                colorWipeDemo(BLACK,0.02,1)

        if runLight:
            RunningLights(0xff,0,0, 0.03,5)
            RunningLights(0xff,0xff,0xff, 0.03,5)
            RunningLights(0,0,0xff, 0.03,5)

        if cylon:
            for i in range(len(colorsList)):
                colorDemos = colorsList[i]
                cylonDemo(colorDemos, 1, 0.03, 0.03,2)
            
        if knightrider:
            knightriderDemo()

        if whiteSparkles:
            whiteSparklesDemo(0.001,300)

        if sparks:
            sparksDemo(0.01,300)

        if firePlace:
            firePlaceDemo(0.01,300)

        if rainbow:
            for i in range(3):
                rainbowDemo(0)
    
        if rainbowCycleDemo:
            for i in range(3):
                rainbow_cycle(.002)

