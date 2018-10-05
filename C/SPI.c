#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <time.h>

#define  SETUP_ERROR -1
const int CHANNEL=1;
const int SPEED=10000;

int main(){
	int status;
	unsigned char data[100];
	data[0]= 0xAA;
	 // if (wiringPiSetupGpio()){
	 // 	printf("Couldn't initialize\n");
	 // 	return SETUP_ERROR;
	 // }
	wiringPiSetup();
	status= wiringPiSPISetup(CHANNEL, SPEED);
	if(status==-1){
		printf("Initialization Failed!\n");
		return SETUP_ERROR;
	}
	printf("Sending data...\n");
	while(1){
		wiringPiSPIDataRW(CHANNEL, data, 1);
		sleep(1);
	}
	return 0;
}
