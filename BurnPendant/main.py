### NeoPixel Pendant/Trinket by Netzer for BRC 2017 :)
## If found please contact pixi@pixelabs.net THANK YOU!!!

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

#strip setup
pixpin = board.D0
leds = 19

pi = neopixel.NeoPixel(pixpin, leds, brightness=ledBright, auto_write=False)


### MAIN LOOP



def flowerd(wait,c1,c2,colorThree):
    pi[0] = colorThree
    for i in range(1,7):
        pi[i] = c1  
    for i in range(7,19):
        pi[i] = c2
    pi.write()
    time.sleep(wait)


def burningManRolld(wait,c1,c2,itr):
    for i in range(itr):
        colorListJewel = [c2,c1,c2,c2,c1,c2]
        colorListRing = [c2,c2,c2,c1,c1,c1,c2,c1,c2,c1,c1,c1]

        pi[0] = c2
        for y in range(6):
            for i in range(len(colorListJewel)):
                tempColorList = shiftList(colorListJewel,y)
                pi[i+1] = tempColorList[i]
        

            for i in range(len(colorListRing)):
                tempColorList = shiftList(colorListRing,y*2)
                pi[i+7] = tempColorList[i]
            pi.write()
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

def sparklesD(clr, wait,itr):
    for i in range(itr):
        pixel = random.randint(0, leds-1)
        clrbool = random.randint(0, 1)       
        if clrbool == 1:
            clrNOW = clr
        else:
            clrNOW = BLACK
        pi[pixel] = clrNOW
        pi.write()
        time.sleep(wait)

def sparksd(wait,itr):
    for i in range(itr):
        sparks_clrLst = [RED,YELLOW,BLACK,ORANGE,GREEN,TEAL,BLACK,CYAN,BLACK,BLUE,PURPLE,MAGENTA,WHITE,BLACK]
        pixel = random.randint(0, leds-1)
        color = random.randint(0, len(clrLst)-1) 
        pi[pixel] = sparks_clrLst[color]
        pi.write()
        time.sleep(wait)

def firePlaced(wait,itr):
    for i in range(itr):
        pixel = random.randint(0, leds-1)
        color = (random.randint(50, 255), random.randint(0, 40), 0)
        pi[pixel] = color
        pi.write()
        time.sleep(wait)
 
def rnbwD(wait):
    for j in range(255):
        for i in range(len(pi)):
            idx = int((i * 256 / len(pi)) + j * 10)
            pi[i] = wheel(idx & 255)
        pi.show()
        time.sleep(wait)
 
def cyD(color, ey, spd, ReturnDelay, itr):
    for i in range (itr):
        for i in range(leds-ey-1):
            setAll(0,0,0)
            pi[i] = color
            for j in range(ey+1):
                pi[i+j] = color
            pi[i+ey+1] = color
            pi.show()
        time.sleep(spd)

        time.sleep(ReturnDelay)

        for i in range(leds-ey-2,-1,-1):
            setAll(0,0,0)
            pi[i] = color
            for j in range(0,ey+1):
                pi[i+j] = color
            pi[i+ey+1] = color
            pi.show()
        time.sleep(spd)

        time.sleep(ReturnDelay)

def setAll(r,g,b):
  for i in range(leds):
    pi[i] = (r,g,b)
  pi.show()

def colorWiped(color, spd, itr):
    for i in range(itr):
        for i in range(leds):
            pi[i] = color
            pi.show()
            time.sleep(spd)

clrLst = [RED,YELLOW,ORANGE,GREEN,TEAL,CYAN,BLUE,PURPLE,MAGENTA,WHITE]
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
        clrNow = random.randint(0, len(clrLst)-1)
    lstclr = clrNow
    while mode == lstMode:
        mode = random.randint(0,8)
    lstMode = mode
    mode=3
   # for i in range(len(clrLst)):
    clrDs = clrLst[clrNow]
    if mode == 0:
        for i in range(5):
            colorWiped(CYAN,spd,1)
            colorWiped(BLACK,spd,1)

    if mode == 1:
        for y in range(2):
            for i in range(len(clrLst)):
                flowerd(spd,clrLst[i],shiftList(clrLst,3)[i],shiftList(clrLst,1)[i])

    if mode == 2:
        for i in range(len(clrLst)-1):
            burningManRolld(spd*10,BLACK,clrLst[i],3)

    if mode == 3:
        for i in range(len(clrLst)):
            burningManRolld(spd*12,clrLst[i],shiftList(clrLst,random.randint(2,5))[i],1)

    if mode == 4:
        sparksd(spd,370)

    if mode == 5:
        sparklesD(RED,0.001,300)

    if mode == 6:
        firePlaced(spd,370)
    
    if mode == 7:
        for i in range(1):
            rnbwD(spd/10)

    if mode == 8:
        cyD(clrDs, 1, spd, spd,15)
