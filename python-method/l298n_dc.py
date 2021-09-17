

import RPi.GPIO as GPIO
from time import sleep

in1 = 17
in2 = 27
en = 18
led = 14
dr = True

GPIO.setmode(GPIO.BCM)
GPIO.setup(in1,GPIO.OUT)
GPIO.setup(in2,GPIO.OUT)
GPIO.setup(en,GPIO.OUT)
GPIO.setup(led,GPIO.OUT)
p=GPIO.PWM(en,1000)

p.start(80)

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
