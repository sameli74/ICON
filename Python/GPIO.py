import RPi.GPIO as GPIO
import time
GPIO.setmode(GPIO.BCM)
GPIO.setup(4, GPIO.OUT)
try:
    while True:
        GPIO.output(4, GPIO.HIGH)
        #time.sleep(0.000001)
        GPIO.output(4, GPIO.LOW)
        #time.sleep(0.000002)
except KeyboardInterrupt:
    GPIO.cleanup()
    print("\nSending is done!")