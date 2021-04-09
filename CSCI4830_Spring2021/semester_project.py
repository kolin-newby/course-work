from microbit import *
from neopixel import *

pixels = 16
OFF = [0, 0, 0]
RED = [10, 0, 0]
RED_B = [50, 0, 0]
GREEN = [0, 10, 0]
YELLOW = [7, 3, 0]

ring = NeoPixel(pin2, pixels)

def range_finder(raw, mx):
    reading = (raw/mx) * 100

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


def read_pulse():
    raw_pulse_data = pin0.read_analog()
    mx = 1023
    ranged_pulse_data = range_finder(raw_pulse_data, mx)
    return ranged_pulse_data


while True:
    top = read_pulse()
    for i in range(0, 8):
        if i <= top:
            ring[i] = GREEN
        else:
            ring[i] = OFF


    for i in range(8, 16):
        ring[i] = RED

    ring.show()
    sleep(50)


    for i in range(8, 16):
        ring[i] = RED_B

    ring.show()
    sleep(50)