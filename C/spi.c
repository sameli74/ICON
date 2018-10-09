#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <time.h>


#define  SETUP_ERROR -1
const int CHANNEL=1;
const int SPEED=3814;

int main(){
	int status;
	unsigned char data[7];
	data[0]= 0x55;
	//wiringPiSetupSys();
	// if (wiringPiSetupGpio()){
	// 	printf("Couldn't initialize\n");
	// 	return SETUP_ERROR;
	// }
	//wiringPiSetup();
	if(wiringPiSPISetup(CHANNEL, SPEED)==-1){
		printf("Initialization Failed!\n");
		return SETUP_ERROR;
	}
	printf("Sending data...\n");
	while(1){
		wiringPiSPIDataRW(CHANNEL, data, 1);
	}
	return 0;


	return 0;

}
