#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <time.h>

#define  SETUP_ERROR -1


int main(){

	if (wiringPiSetupGpio()){
		printf("Couldn't initialize\n");
		return SETUP_ERROR;
	}




	return 0;
}
