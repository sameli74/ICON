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
	//wiringPiSetup();
	wiringPiSPISetup(CHANNEL, SPEED);
	printf("Sending data...\n");
	while(1){
		wiringPiSPIDataRW(CHANNEL, data, 1);
	}
	return 0;

}
