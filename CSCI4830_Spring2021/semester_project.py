from microbit import *
from neopixel import *
import utime

pixels = 16

OFF = [0, 0, 0]

RED = [10, 0, 0]
RED_B = [30, 0, 0]

GREEN = [0, 10, 0]
GREEN_B = [0, 30, 0]

YELLOW = [7, 3, 0]
YELLOW_B = [21, 9, 0]

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
    return pin0.read_analog()

beat_cnt = 0
HR = 0
start_time = utime.ticks_ms()

while True:
    pulse = read_pulse()
    ranged_pulse = range_finder(pulse, 1023)

    if utime.ticks_diff(utime.ticks_ms(), start_time) >= 15000:
        HR = beat_cnt * 4
        beat_cnt = 0
        start_time = utime.ticks_ms()

    if pulse > 600:
        for i in range(0, 8):
            if i <= ranged_pulse:
                ring[i] = GREEN_B
            else:
                ring[i] = OFF

        beat_cnt += 1
    else:
        for i in range(0, 8):
            if i <= ranged_pulse:
                ring[i] = GREEN
            else:
                ring[i] = OFF

    ring.show()