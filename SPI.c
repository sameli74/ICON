#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <time.h>

#define -1 SETUP_ERROR

int main(){

	if (wiringPiSetupGpio())
		printf("Couldn't initialize\n");
		else{
			printf("Initialization was successful\n");
			return
		}


	return 0;
}
