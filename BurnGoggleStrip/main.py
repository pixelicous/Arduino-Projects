### NeoPixel Pendant/Trinket by Pixel for BRC 2017 :)
## If found please contact pixi@pixelabs.net THANK YOU!!!

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

ledBright = 0.08

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
        ledBright = 0.08

pi = neopixel.NeoPixel(pixpin, num_leds, brightness=ledBright, auto_write=False)

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

clrsList = [RED,YELLOW,ORANGE,GREEN,TEAL,CYAN,BLUE,PURPLE,MAGENTA,WHITE]

def sparklesD(clr, wait,itr):
    for i in range(itr):
        pixel = random.randint(0, num_leds-1)
        clrbool = random.randint(0, 1)       
        if clrbool == 1:
            clrNOW = clr
        else:
            clrNOW = BLACK
        pi[pixel] = clrNOW
        pi.write()
        time.sleep(wait)
        
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

def swirl_colour(start, pix, rc):
    off = (pix - start) & 0x0F
    if(off < 4):
        amt = intpow(2, off+4)
        if (rc==0):
            clr = (0, amt,0)
        if (rc==1):
            clr = (amt, 0,0)
        if (rc==2):
            clr = (0, 0, amt)
        return clr
    else:
        return BLACK

def loop_swirl(itr, spd):
    for i in range(itr):
        backc = random.randint(0,1)
        rc = random.randint(0,2)
        for y in range(8):
            for led in range(num_leds):
                pi[led] = swirl_colour(y, led, rc)
                
            pi.show()
            time.sleep(spd)
        if backc==1:
            for y in range(8,-2,-2):
                for led in range(num_leds):
                    pi[led] = swirl_colour(y, led, rc)
                    
                pi.show()
                time.sleep(spd)

def cylonD(clr, eye, spd, ReturnDelay, itr):
    for i in range (itr):
        for i in range(num_leds-eye-1):
            setAll(0,0,0)
            pi[i] = clr
            for j in range(eye+1):
                pi[i+j] = clr
            pi[i+eye+1] = clr
            pi.show()
        time.sleep(spd)

        time.sleep(ReturnDelay)

        for i in range(num_leds-eye-2,-1,-1):
            setAll(0,0,0)
            pi[i] = clr
            for j in range(0,eye+1):
                pi[i+j] = clr
            pi[i+eye+1] = clr
            pi.show()
        time.sleep(spd)

        time.sleep(ReturnDelay)

def clrWipeD(clr, spd, itr):
    for i in range(itr):
        for i in range(num_leds):
            pi[i] = clr
            pi.show()
            time.sleep(spd)

def theaterD(clr, spd, itr):
    for i in range(itr):
        for q in range(2):
            for i in range(0,num_leds,2):
                pi[i+q] = clr
            pi.show()
            time.sleep(spd)
            for i in range(0,num_leds,2):
                pi[i+q] = BLACK

def futter(clr, spd, itr):
    for i in range(itr):
        for j in range(num_leds):
            pi[j] = clr
        pi.show() 
        time.sleep(spd)
        for j in range(num_leds):
            pi[j] = BLACK
        pi.show() 
        time.sleep(spd)


def breath(clr, spd, itr):
    for i in range(itr):
        for i in range(235):
            if (clr == 0): setAll(i+15,0,0)
            if (clr == 1): setAll(0,i+15,0)
            else: setAll(0,0,i+15) 
        time.sleep(spd)
        for i in range(255,15,-1):
            if (clr == 0): setAll(i-15,0,0)
            if (clr == 1): setAll(0,i-15,0)
            else: setAll(0,0,i-15)
        time.sleep(spd)
        setAll(0,0,0)

def rbw_cycle(wait,itr):
    for i in range(itr):
        for j in range(255):
            for i in range(len(pi)):
                idx = int((i * 256 / len(pi)) + j * 10)
                pi[i] = wheel(idx & 255)
            pi.show()
            time.sleep(wait)

def setAll(red, green, blue):
  for i in range(num_leds):
    pi[i] = (red, green, blue)
  pi.show()


clrsList = [RED,YELLOW,ORANGE,GREEN,TEAL,CYAN,BLUE,PURPLE,MAGENTA,WHITE]
lstclr = 0
clrNow = 0
lstMode = 0
mode = 0
lstSpd = 0
spd = 0
while True:
    while spd == lstSpd:
        spd = random.uniform(0.02, 0.08)
    lstSpd = spd
    while clrNow == lstclr:
        clrNow = random.randint(0, len(clrsList)-1)
    lstclr = clrNow
    while mode == lstMode:
        mode = random.randint(0,7)
    lstMode = mode

   # for i in range(len(clrsList)):
    clrDs = clrsList[clrNow]

    if mode == 7:
        clrDS = random.randint(0,5)
        breath(clrDs,0.01,2)
        
    if mode == 6:
        futter(clrDs,spd*2.5,23)

    if mode == 5:
        loop_swirl(35, spd)

    if mode == 4:
            theaterD(clrDs,spd,35)

    if mode == 3:
        for i in range(20):
            clrWipeD(clrDs,spd,1)
            clrWipeD(BLACK,spd,1)

    if mode == 2:
        rbw_cycle(.002,2)

    if mode == 1:
            cylonD(clrDs, 1, spd, spd,35)
        
    if mode == 0:
        sparklesD(clrDs, spd,300)
