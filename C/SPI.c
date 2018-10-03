#include <stdio.h>
#include <stdlib.h>
#include <wiringPiSPI.h>
#include <wiringPi.h>
#include <time.h>

int main(){

	if (wiringPiSetupGpio())
		printf("Couldn't initialize\n");
	else
		printf("Initialization was successful");


	return 0;
}
