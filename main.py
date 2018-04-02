import time
import RPi.GPIO as GPIO
GPIO.setmode(GPIO.BOARD)
GPIO.setwarnings(False)
GPIO.setup(11, GPIO.IN)

while True:
    if GPIO.input(11) == GPIO.LOW:
        print("Low")
    else:
        print("High")
    time.sleep(0.01)





GPIO.cleanup()