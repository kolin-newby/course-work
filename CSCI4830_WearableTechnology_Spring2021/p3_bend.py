from microbit import *
import music

reference_res = 8.2;

tune = ["F4:4"]

while True:
    Vout = pin2.read_analog();
    if Vout < 1023:
        resistance = (reference_res * Vout) / (1023 - Vout)
        if resistance > 100:
            music.play(tune)
    else:
        continue