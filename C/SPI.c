/*
 * spiSpeed.c:
 *	Code to measure the SPI speed/latency.
 *	Copyright (c) 2014 Gordon Henderson
 ***********************************************************************
 * This file is part of wiringPi:
 *	https://projects.drogon.net/raspberry-pi/wiringpi/
 *
 *    wiringPi is free software: you can redistribute it and/or modify
 *    it under the terms of the GNU Lesser General Public License as
 *    published by the Free Software Foundation, either version 3 of the
 *    License, or (at your option) any later version.
 *
 *    wiringPi is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU Lesser General Public License for more details.
 *
 *    You should have received a copy of the GNU Lesser General Public
 *    License along with wiringPi.
 *    If not, see <http://www.gnu.org/licenses/>.
 ***********************************************************************
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdint.h>
#include <string.h>
#include <errno.h>
//#include <fcntl.h>
//#include <sys/ioctl.h>
//#include <linux/spi/spidev.h>

#include <wiringPi.h>
#include <wiringPiSPI.h>

#define	TRUE	(1==1)
#define	FALSE	(!TRUE)

#define	SPI_CHAN		0
#define	NUM_TIMES		100
#define	MAX_SIZE		(1024*1024)

static int myFd ;


void spiSetup (int speed)
{
  if ((myFd = wiringPiSPISetup (SPI_CHAN, speed)) < 0)
  {
    fprintf (stderr, "Can't open the SPI bus: %s\n", strerror (errno)) ;
    exit (EXIT_FAILURE) ;
  }
}


int main (void)
{
  int speed, times, size ;
  unsigned int start, end ;
  int spiFail ;
  unsigned char *myData ;
  double timePerTransaction, perfectTimePerTransaction, dataSpeed ;

  if ((myData = malloc (MAX_SIZE)) == NULL)
  {
    fprintf (stderr, "Unable to allocate buffer: %s\n", strerror (errno)) ;
    exit (EXIT_FAILURE) ;
  }

  wiringPiSetup () ;

  for (speed = 1 ; speed <= 32 ; speed *= 2)
  {
    printf ("+-------+--------+----------+----------+-----------+------------+\n") ;
    printf ("|   MHz |   Size | mS/Trans |      TpS |    Mb/Sec | Latency mS |\n") ;
    printf ("+-------+--------+----------+----------+-----------+------------+\n") ;

    spiFail = FALSE ;
    spiSetup (speed * 1000000) ;
    for (size = 1 ; size <= MAX_SIZE ; size *= 2)
    {
      printf ("| %5d | %6d ", speed, size) ;

      start = millis () ;
      for (times = 0 ; times < NUM_TIMES ; ++times)
	if (wiringPiSPIDataRW (SPI_CHAN, myData, size) == -1)
	{
	  printf ("SPI failure: %s\n", strerror (errno)) ;
	  spiFail = TRUE ;
	  break ;
	}
      end = millis () ;

      if (spiFail)
	break ;

      timePerTransaction        = ((double)(end - start) / (double)NUM_TIMES) / 1000.0 ;
      dataSpeed                 =  (double)(size * 8)    / (1024.0 * 1024.0) / timePerTransaction  ;
      perfectTimePerTransaction = ((double)(size * 8))   / ((double)(speed * 1000000)) ;

      printf ("| %8.3f ", timePerTransaction * 1000.0) ;
      printf ("| %8.1f ", 1.0 / timePerTransaction) ;
      printf ("| %9.5f ", dataSpeed) ;
      printf ("|   %8.5f ", (timePerTransaction - perfectTimePerTransaction) * 1000.0) ;
      printf ("|\n") ;

    }

    close (myFd) ;
    printf ("+-------+--------+----------+----------+-----------+------------+\n") ;
    printf ("\n") ;
  }

  return 0 ;
}

// #include <stdio.h>
// #include <stdlib.h>
// #include <wiringPiSPI.h>
// #include <wiringPi.h>
// #include <time.h>
//
// #define  SETUP_ERROR -1
// const int CHANNEL=1;
// const int SPEED=10000;
//
// int main(){
// 	int status;
// 	unsigned char data[100];
// 	data[0]= 0xAA;
// //	 if (wiringPiSetupGpio()){
// //	 	printf("Couldn't initialize\n");
// //	 	return SETUP_ERROR;
// //	 }
// 	wiringPiSetup();
// 	status= wiringPiSPISetup(CHANNEL, SPEED);
// 	if(status==-1){
// 		printf("Initialization Failed!\n");
// 		return SETUP_ERROR;
// 	}
// 	printf("Sending data...\n");
// 	while(1){
// 		wiringPiSPIDataRW(CHANNEL, data, 1);
// 	}
// 	return 0;
// }
