#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <time.h>

#define -1 SETUP_ERROR


int main(){

	if (wiringPiSetupGpio()){
		printf("Couldn't initialize\n");
		return SETUP_ERROR;
	}
	PinMode(12, OUTPUT);

	while(1){
		//delay() based on milisecond
		delayMicroseconds(100);
		digitalWrite(12, HIGH);
		delayMicroseconds(100);
		digitalWrite(12, LOW);
	}




	return 0;
}
