#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include "functions.h"

#define FILE_PATH "input.txt"
#define READ_SIZE 304
#define FILE_SIZE 1024

int size_in_byte(FILE* pFile){
  int bytes_num;
  fseek (pFile , 0 , SEEK_END);
  bytes_num = ftell (pFile);
  rewind (pFile);
  printf("size of file in bytes:%d\n", bytes_num);
  return bytes_num;
}
FILE* read_file(int* bytes_num){
  FILE * pFile;
  pFile = fopen ( FILE_PATH , "rb" );
  if (pFile==NULL){
    fputs ("File error",stderr);
    exit (1);
  }
  *bytes_num=size_in_byte(pFile);
  return pFile;
}

char* initialization(FILE * pFile){
		char * buffer;	  
		int bytes_num; 
	  //pFile=read_file(&bytes_num);
	  buffer = (char*) malloc (sizeof(char)*(FILE_SIZE));
	  if (buffer == NULL){
   	 fputs ("Memory error",stderr);
   	 exit (2);
  		}
 	 if (!bcm2835_init()){
 	 	printf("bcm2835_init failed. Are you running as root??\n");
      exit (2);
      }
 	if (!bcm2835_spi_begin()){
  		printf("bcm2835_spi_begin failed. Are you running as root??\n");
      exit (2);
  }
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_4096); 
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
	return buffer;
}