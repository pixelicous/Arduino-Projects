
def starPowerDemo2(wait,colorOne,colorTwo):
     colorListRing = [colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne]
   
     for y in range(6):
         for i in range(0,7):            
             pixels[i] = colorTwo

         for i in range(len(colorListRing)):
             tempColorList = shiftList(colorListRing,y)
             pixels[i+7] = tempColorList[i]
             #pixels[0] = tempColorList[i]
         pixels.write()
         time.sleep(wait) 


def starPowerDemo(wait,colorOne,colorTwo):
     colorListRing = [colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne,colorTwo,colorOne]
   
     for y in range(2):
         for i in range(1,7):            
             pixels[i] = colorTwo

         for i in range(len(colorListRing)):
             tempColorList = shiftList(colorListRing,y)
             pixels[i+7] = tempColorList[i]
             pixels[0] = colorListRing[i]
         pixels.write()
         time.sleep(wait) 