import RPi.GPIO as GPIO
import spidev
import time
#import wiringpi as wp
spi = spidev.SpiDev()
spi.open(0,0)
spi.max_speed_hz= 10000
print("Sending information...")
try:
    while True:
        #resp = spi.writebytes([0xAA])
        resp = spi.xfer2([0xAA])
        time.sleep(0.002)
        #print("message sent!")
except KeyboardInterrupt:
    spi.close()
    GPIO.cleanup()
    print("\nSending is done!")



#GPIO.setwarnings(False)
#GPIO.setmode(GPIO.BCM)
#GPIO.setup(12, GPIO.OUT)

#GPIO.output(12,GPIO.HIGH)
