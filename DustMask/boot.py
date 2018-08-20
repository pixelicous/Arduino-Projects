import storage
import touchio
import board
import time
import digitalio

led = digitalio.DigitalInOut(board.D1)
led.direction = digitalio.Direction.OUTPUT

touch_pad = board.D2
touch = touchio.TouchIn(touch_pad)
touched = False

led.value = True
time.sleep(30)

for i in range(100000):
    if touch.value:
        touched = True

print(touched)
storage.remount("/", touched)