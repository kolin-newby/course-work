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
    increment = ((mx * (1/8)) / mx) * 100
    reading = (raw/mx) * 100


    if reading >= 0 and reading <= increment:
        return 0
    if reading > increment and reading <= (increment * 2):
        return 1
    if reading > (increment * 2) and reading <= (increment * 3):
        return 2
    if reading > (increment * 3) and reading <= (increment * 4):
        return 3
    if reading > (increment * 4) and reading <= (increment * 5):
        return 4
    if reading > (increment * 5) and reading <= (increment * 6):
        return 5
    if reading > (increment * 6) and reading <= (increment * 7):
        return 6
    if reading > (increment * 7) and reading <= (increment * 8):
        return 7
    else:
        return 7


def read_pulse():
    return pin0.read_analog()

beat = False
beat_cnt = 0
HR = -1
start_time = utime.ticks_ms()

while True:
    pulse = read_pulse()
    if HR != -1:
        ranged_pulse = range_finder(HR, 180)
    else:
        ranged_pulse = 0

    if utime.ticks_diff(utime.ticks_ms(), start_time) >= 7500:
        HR = beat_cnt * 8
        beat_cnt = 0
        start_time = utime.ticks_ms()

    if pulse > 625 and beat == False:
        for i in range(0, 8):
            if i <= ranged_pulse:
                if ranged_pulse <= 1:
                    ring[i] = RED_B
                elif ranged_pulse > 1 and ranged_pulse <= 5:
                    ring[i] = GREEN_B
                else:
                    ring[i] = RED_B
            else:
                ring[i] = OFF

        beat = True
        beat_cnt += 1
    else:
        if pulse < 500:
            beat = False
        for i in range(0, 8):
            if i <= ranged_pulse:
                if ranged_pulse <= 1:
                    ring[i] = RED
                elif ranged_pulse > 1 and ranged_pulse <= 5:
                    ring[i] = GREEN
                else:
                    ring[i] = RED
            else:
                ring[i] = OFF

    ring.show()