#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <time.h>

#define  SETUP_ERROR -1
const int CHANNEL=0;
const int SPEED=100000;

int main(){
	int status;
	unsigned char data[1];
	data[0]= 0xAA;
	if (wiringPiSetupGpio()){
		printf("Couldn't initialize\n");
		return SETUP_ERROR;
	}
status= wiringPiSPISetup(CHANNEL, SPEED);
if(status==-1){
	printf("something wrong happened!\n");
	return SETUP_ERROR;
}
printf("Sending data...\n");
while(1){
	wiringPiSPIDataRW(CHANNEL, data, 1);
	delayMicroseconds(1000);
}
return 0;



	return 0;
}
