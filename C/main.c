#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include "functions.h"

#define READ_SIZE 304

int main () {
  FILE * pFile;
  int bytes_num;
  char * buffer;
  int result;
  pFile=read_file(&bytes_num);
  buffer = (char*) malloc (sizeof(char)*(READ_SIZE+1));
  if (buffer == NULL){
    fputs ("Memory error",stderr);
    exit (2);
  }
  if (!bcm2835_init()){
 		printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
  }
  if (!bcm2835_spi_begin()){
  		printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
  }
  bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);
  bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);
  bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_2048); 
  bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
  bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);
  while(1){
    result = fread (buffer+1,1,READ_SIZE,pFile);
	*buffer='©';    
    if(result==0)
      break;
    printf("Read bytes: %d\n", result);
//    printf("final character: %c\n", buffer[result]);
//uint8_t send_data = 0xAA;
    //const char send_data[1]={0xAA};
    //while(1){
      bcm2835_spi_writenb(buffer, result+1);
      delay(10);
    //result = fread (buffer,1,READ_SIZE,pFile);
   // if(result==0)
     // break;
    //printf("Read bytes: %d\n", result);
    //printf("final character: %c\n", buffer[result-1]);
//uint8_t send_data = 0xAA;
    //const char send_data[1]={0xAA};
    //while(1){
      //bcm2835_spi_writenb(buffer, result);
    }
    // printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data, read_data);
    // if (send_data != read_data)
    //   printf("Do you have the loopback from MOSI to MISO connected?\n");
	//}
  bcm2835_spi_end();
  bcm2835_close();
  fclose (pFile);
  free (buffer);
  return 0;
}
