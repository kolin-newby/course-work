from microbit import *
import time
import music

class Lamp:
    lit = 1
    state = "solid"

    def __init__(self):
        self.lit = 0
        self.state = "strobe"

    def toggle_lit(self):
        if self.lit:
            self.lit = 0
        else:
            self.lit = 1

    def toggle_state(self):
        if self.state == "solid":
            self.state = "strobe"
        else:
            self.state = "solid"


l1 = Lamp()

tune = ["E4:4"]

while True:
    if l1.lit and l1.state == "solid":
        pin16.write_analog(1023)
    if not l1.lit:
        pin16.write_analog(0)
    if l1.lit and l1.state == "strobe":
        pin16.write_analog(1023)
        sleep(250)
        pin16.write_analog(0)
        sleep(250)
    if pin0.is_touched():
        held = False
        start = time.ticks_ms()
        while pin0.is_touched():
            if time.ticks_diff(time.ticks_ms(), start) >= 2500:
                music.play(tune)
                held = True
                l1.toggle_state()
        if not held:
            l1.toggle_lit()
            sleep(250)