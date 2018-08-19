### NeoPixel Pendant/Trinket by Pixel 2018
 
import time
import d

#Demos to run
colorWipe = 0
flower = 0
starPower = 0
sparks = 0
whiteSparkles = 0
firePlace = 0
burningManRoll = 0
burningManRollColors = 0
rainbowDemo = 1
rainbowCycleDemo = 1
sliceAlternating = 0

#add sets of demos
#use bootrom to jump between sets
#have a set with all demos
#add a demo that does outer ring circle then inner, can go out and in- in same function
# Constants

### MAIN LOOP

while True:
    if colorWipe:
        for i in range(5):
            d.colorWipeDemo(d.CYAN,0.02,1)
            d.colorWipeDemo(d.BLACK,0.02,1)

    if starPower:
         for i in range(len(d.colorsList)):
             starPowerDemo(0.05,d.RED,d.BLUE)

    if flower:
        for y in range(2):
            for i in range(len(d.colorsList)):
                d.flowerDemo(0.2,d.colorsList[i],d.shiftList(d.colorsList,3)[i],d.shiftList(d.colorsList,1)[i])

    if burningManRoll:
        for i in range(len(d.colorsList)-1):
            d.burningManRollDemo(0.5,d.BLACK,d.colorsList[i])

    if burningManRollColors:
        for i in range(len(d.colorsList)):
            d.burningManRollDemo(0.1,d.colorsList[i],d.shiftList(d.colorsList,3)[i])

    if sparks:
        d.sparksDemo(0.01,370)

    if whiteSparkles:
        d.whiteSparklesDemo(0.001,300)

    if firePlace:
        d.firePlaceDemo(0.01,370)
    
    if rainbowDemo:
        for i in range(1):
            d.rainbow(.002)
 
    if rainbowCycleDemo:
        for i in range(1):
            d.rainbow_cycle(.002)