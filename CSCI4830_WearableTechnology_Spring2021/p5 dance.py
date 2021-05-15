from microbit import *
import utime


class beat:
    tempo = 0
    note_spacing = 0.0
    units_per_bar = 4
    beat_unit = 4

    def __init__(self, tempo, beat_unit, units_per_bar):
        self.tempo = tempo
        self.units_per_bar = units_per_bar
        self.beat_unit = beat_unit
        self.note_spacing = 60/tempo

    def set_tempo(self):
        count = 0
        times = []
        flag = True
        while button_b.is_pressed() and flag:
            display.show([Image.DIAMOND_SMALL, Image.DIAMOND], wait=True, loop=False, clear=True)
        flag = False
        t1 = 0
        t2 = 0
        while count <= 9:
            if button_b.is_pressed():
                if t1 == 0:
                    t1 = utime.ticks_ms()
                    continue
                t2 = t1
                t1 = utime.ticks_ms()
                times.append(utime.ticks_diff(t1, t2))
                count += 1
                display.set_pixel(2,2,9)
                sleep(100)
                display.set_pixel(2,2,0)
        sec_per_beat = (sum(times)/len(times))/1000
        self.note_spacing = sec_per_beat
        self.tempo = ((1/sec_per_beat)+0.1) * 60
        display.show([Image.DIAMOND, Image.DIAMOND_SMALL], wait=True, loop=False, clear=True)
        return

pin0.write_digital(1)
song = beat(120, 4, 4)
first_beat = 0
while True:
    if button_b.is_pressed():
        start = utime.ticks_ms()
        while button_b.is_pressed():
            if (utime.ticks_ms() - start) > 3000:
                song.set_tempo()
                break
    if first_beat == 0:
        pin0.write_digital(0)
        pin1.write_digital(0)
        display.show(Image.DIAMOND, wait=False, loop=False, clear=True)
        sleep(80)
        pin0.write_digital(1)
        pin1.write_digital(1)
        sleep(((song.note_spacing)*1000)-80)
    elif first_beat == (song.units_per_bar - 1):
        pin0.write_digital(0)
        display.show(Image.DIAMOND_SMALL, wait=False, loop=False, clear=True)
        sleep(80)
        pin0.write_digital(1)
        sleep(((song.note_spacing)*1000)-80)
        first_beat = 0
        continue
    else:
        pin0.write_digital(0)
        display.show(Image.DIAMOND_SMALL, wait=False, loop=False, clear=True)
        sleep(80)
        pin0.write_digital(1)
        sleep(((song.note_spacing)*1000)-80)
    first_beat += 1