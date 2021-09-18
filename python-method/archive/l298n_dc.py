

import RPi.GPIO as GPIO
from time import sleep

led = 14
dr = True

GPIO.setmode(GPIO.BCM)
import defRobot
GPIO.setup(led,GPIO.OUT)
GPIO.output(led,GPIO.HIGH)

while(1):
    
    x=input()

    if x=='r':
        print("run")
        if(dr):
            GPIO.output(in1,GPIO.LOW)
            GPIO.output(in2,GPIO.HIGH)
        else:
            GPIO.output(in1,GPIO.HIGH)
            GPIO.output(in2,GPIO.LOW)
        x='z'

    elif x == 'd':
        dr = not dr
        x='r'

    elif x == 's':
        print("stop")
        GPIO.output(in1,GPIO.LOW)
        GPIO.output(in2,GPIO.LOW)
        x='z'

    elif x == 'l':
        print('low')
        p.ChangeDutyCycle(80)

    elif x == 'm':
        print('low')
        p.ChangeDutyCycle(90)
        x='z'

    elif x == 'h':
        print('high')
        p.ChangeDutyCycle(100)
        x='z'

    elif x == 'e':
        GPIO.cleanup()
        print("GPIO Clean up")
        break

    else:
        print("<<< wrong data >>>")
        print("please enter the defined data to continue.....")
        x='z'
