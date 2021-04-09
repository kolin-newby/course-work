from microbit import *
from neopixel import *

pixels = 16

ring = NeoPixel(pin2, pixels)

#red = [128, 0, 0]
#green = [0, 128, 0]
#yellow = [89, 39, 0]

red = [8, 0, 0]
green = [0, 8, 0]
yellow = [6, 2, 0]

def range_finder(raw, mx):
    reading = (raw/mx)*100

    if reading >= 0 and reading <= 12.5:
        return 0
    if reading > 12.5 and reading <= 25:
        return 1
    if reading > 25 and reading <= 37.5:
        return 2
    if reading > 37.5 and reading <= 50:
        return 3
    if reading > 50 and reading <= 62.5:
        return 4
    if reading > 62.5 and reading <= 75:
        return 5
    if reading > 75 and reading <= 87.5:
        return 6
    if reading > 87.5 and reading <= 100:
        return 7
    else:
        return 7


while True:
    for i in range(0, 8):
        ring[i] = yellow
    for i in range(8, 16):
        ring[i] = green

    ring.show()