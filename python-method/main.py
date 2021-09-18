

import RPi.GPIO as GPIO
from time import sleep

led = 14

GPIO.setmode(GPIO.BCM)
from defRobot import *
GPIO.setup(led,GPIO.OUT)
GPIO.output(led,GPIO.HIGH)

x = 'z'

def wheel(a, b, c, d):
    if(c or d == 0):
        dr = d
    else:
        if(d==1):
            dr = 2
        else:
            dr = 1

    if(dr == 0):
        GPIO.output(a, GPIO.LOW)
        GPIO.output(b, GPIO.LOW)
    elif(dr == 1):
        GPIO.output(a, GPIO.HIGH)
        GPIO.output(b, GPIO.LOW)
    else:
        GPIO.output(a, GPIO.LOW)
        GPIO.output(b, GPIO.HIGH)

def allwheel(a, b, c, d):
    wheel(in1_fl, in2_fl, orientNorm_fl, a)
    wheel(in1_fr, in2_fr, orientNorm_fr, b)
    wheel(in1_bl, in2_bl, orientNorm_bl, c)
    wheel(in1_br, in2_br, orientNorm_br, d)

def direct(d):
    if(d=='8'): #Forward
        allwheel(1,1,1,1)
    elif(d=='2'): #Backward
        allwheel(2,2,2,2)
    elif(d=='4'): #Left
        allwheel(2,1,1,2)
    elif(d=='6'): #Right
        allwheel(1,2,2,1)
    elif(d=='7'): #FL
        allwheel(0,1,1,0)
    elif(d=='9'): #FR
        allwheel(1,0,0,1)
    elif(d=='1'): #BL
        allwheel(2,0,0,2)
    elif(d=='3'): #BR
        allwheel(0,2,2,0)
    elif(d==','): #rotate left
        allwheel(2,1,2,1)
    elif(d=='.'): #rotate right
        allwheel(1,2,1,2)
    else:
        allwheel(0,0,0,0)

while(1):
    
    if x=='z':
        x=input()

    if x == 'e':
        GPIO.cleanup()
        print("GPIO Clean up")
        break

    else:
        direct(x)
        x='z'

