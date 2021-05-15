from microbit import *
import music

def sound3():
    for freq in range(880, 1173, 146):
        music.pitch(freq, 6)
        sleep(135)

def sound2():
    for freq in range(1173, 1466, 146):
        music.pitch(freq, 6)
        sleep(115)

def sound1():
    for freq in range(1466, 1760, 146):
        music.pitch(freq, 6)
        sleep(95)

def rng1(h):
    if h >= 344 or h <= 16:
        return True
    else:
        return False

def rng2(h):
    if (h >= 328 and h < 344) or (h <= 32 and h > 16):
        return True
    else:
        return False

def rng3(h):
    if (h >= 312 and h < 328) or (h <= 48 and h > 32):
        return True
    else:
        return False

compass.calibrate()
while True:
    heading = compass.heading()
    if rng1(heading):
        sound1()
    if rng2(heading):
        sound2()
    if rng3(heading):
        sound3()
    else:
        pass