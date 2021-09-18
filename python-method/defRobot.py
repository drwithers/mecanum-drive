# This file defines the configuration of the robot
import RPi.GPIO as GPIO

startpwm = 100
pwmfreq = 1000

#FRONT LEFT
in1_fl = 17
in2_fl = 27
en_fl = 18
orientNorm_fl = False

#FRONT RIGHT
in1_fr = 4
in2_fr = 3
en_fr = 12
orientNorm_fr = False

#BACK LEFT
in1_bl = 10
in2_bl = 9
en_bl = 13
orientNorm_bl = True

#BACK RIGHT
in1_br = 20
in2_br = 21
en_br = 19
orientNorm_br = True

def setup_wheel(a, b, en):
    GPIO.setup(a,GPIO.OUT)
    GPIO.setup(b,GPIO.OUT)
    GPIO.setup(en,GPIO.OUT)
    return GPIO.PWM(en,pwmfreq)

p_fl = setup_wheel(in1_fl,in2_fl,en_fl)
p_fr = setup_wheel(in1_fr,in2_fr,en_fr)
p_bl = setup_wheel(in1_bl,in2_bl,en_bl)
p_br = setup_wheel(in1_br,in2_br,en_br)

p_fl.start(startpwm)
p_fr.start(startpwm)
p_bl.start(startpwm)
p_br.start(startpwm)
