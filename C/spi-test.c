// spi.c
//
// Example program for bcm2835 library
// Shows how to interface with SPI to transfer a byte to and from an SPI device
//
// After installing bcm2835, you can build this
// with something like:
// gcc -o spi spi.c -l bcm2835
// sudo ./spi
//
// Or you can test it before installing with:
// gcc -o spi -I ../../src ../../src/bcm2835.c spi.c
// sudo ./spi
//
// Author: Mike McCauley
// Copyright (C) 2012 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $
#include <bcm2835.h>
#include <stdio.h>
int main(int argc, char **argv)
{
    // If you call this, it will not actually access the GPIO
    // Use for testing
    //        bcm2835_set_debug(1);
    if (!bcm2835_init())
    {
      printf("bcm2835_init failed. Are you running as root??\n");
      return 1;
    }
    if (!bcm2835_spi_begin())
    {
      printf("bcm2835_spi_begin failed. Are you running as root??\n");
      return 1;
    }
    bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_16); // The default
    bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default

    // Send a byte to the slave and simultaneously read a byte back from the slave
    // If you tie MISO to MOSI, you should read back what was sent
    //uint8_t send_data = 0xAA;
    const char send_data[20]={0xAA, 0xAA,0xAA, 0xAA,
                      0xAA, 0xAA,0xAA, 0xAA,
                      0xAA, 0xAA,0xAA, 0xAA,
                      0xAA, 0xAA,0xAA, 0xAA,
                      0xAA, 0xAA,0xAA, 0xAA}
    while(1){
      bcm2835_spi_writenb(send_data,20);
    }
    // printf("Sent to SPI: 0x%02X. Read back from SPI: 0x%02X.\n", send_data, read_data);
    // if (send_data != read_data)
    //   printf("Do you have the loopback from MOSI to MISO connected?\n");
    bcm2835_spi_end();
    bcm2835_close();
    return 0;

    // if (!bcm2835_init()){
    // 	printf("bcm2835_init failed. Are you running as root??\n");
    // 	return 1;
    // }
    // bcm2835_spi_begin();
    //
    // //Set CS pins polarity to low
    // // bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, 0);
    // // bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS1, 0);
    // // std::cerr<<"2";
    //
    // //Set SPI clock speed
    // //	BCM2835_SPI_CLOCK_DIVIDER_65536 = 0,       ///< 65536 = 262.144us = 3.814697260kHz (total H+L clock period)
    // //	BCM2835_SPI_CLOCK_DIVIDER_32768 = 32768,   ///< 32768 = 131.072us = 7.629394531kHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_16384 = 16384,   ///< 16384 = 65.536us = 15.25878906kHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_8192  = 8192,    ///< 8192 = 32.768us = 30/51757813kHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_4096  = 4096,    ///< 4096 = 16.384us = 61.03515625kHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_2048  = 2048,    ///< 2048 = 8.192us = 122.0703125kHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_1024  = 1024,    ///< 1024 = 4.096us = 244.140625kHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_512   = 512,     ///< 512 = 2.048us = 488.28125kHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_256   = 256,     ///< 256 = 1.024us = 976.5625MHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_128   = 128,     ///< 128 = 512ns = = 1.953125MHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_64    = 64,      ///< 64 = 256ns = 3.90625MHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_32    = 32,      ///< 32 = 128ns = 7.8125MHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_16    = 16,      ///< 16 = 64ns = 15.625MHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_8     = 8,       ///< 8 = 32ns = 31.25MHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_4     = 4,       ///< 4 = 16ns = 62.5MHz
    // //	BCM2835_SPI_CLOCK_DIVIDER_2     = 2,       ///< 2 = 8ns = 125MHz, fastest you can get
    // //	BCM2835_SPI_CLOCK_DIVIDER_1     = 1,       ///< 1 = 262.144us = 3.814697260kHz, same as 0/65536
    // // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_1);
    // // std::cerr<<"3";
    //
    // bcm2835_spi_setBitOrder(BCM2835_SPI_BIT_ORDER_MSBFIRST);      // The default
    // bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);                   // The default
    // bcm2835_spi_setClockDivider(BCM2835_SPI_CLOCK_DIVIDER_65536); // The default
    // bcm2835_spi_chipSelect(BCM2835_SPI_CS0);                      // The default
    // bcm2835_spi_setChipSelectPolarity(BCM2835_SPI_CS0, LOW);      // the default
    //
    // //Set SPI data mode
    // //	BCM2835_SPI_MODE0 = 0,  // CPOL = 0, CPHA = 0, Clock idle low, data is clocked in on rising edge, output data (change) on falling edge
    // //	BCM2835_SPI_MODE1 = 1,  // CPOL = 0, CPHA = 1, Clock idle low, data is clocked in on falling edge, output data (change) on rising edge
    // //	BCM2835_SPI_MODE2 = 2,  // CPOL = 1, CPHA = 0, Clock idle high, data is clocked in on falling edge, output data (change) on rising edge
    // //	BCM2835_SPI_MODE3 = 3,  // CPOL = 1, CPHA = 1, Clock idle high, data is clocked in on rising, edge output data (change) on falling edge
    // // bcm2835_spi_setDataMode(BCM2835_SPI_MODE0);		//(SPI_MODE_# | SPI_CS_HIGH)=Chip Select active high, (SPI_MODE_# | SPI_NO_CS)=1 device per bus no Chip Select
    // // std::cerr<<"4";
    //
    // //Set with CS pin to use for next transfers
    // // bcm2835_spi_chipSelect(BCM2835_SPI_CS0);
    // // std::cerr<<"5";
    //
    // //Transfer 1 byte
    // printf("sending data...")
    // uint8_t data;
    // while(1){
    // 	data = bcm2835_spi_transfer((uint8_t)0xAA);
    // 	delayMicroseconds(100);
    // }
    //
    // //Transfer many bytes
    // // char data_buffer[10];
    // // int Count;
    // // for (Count = 0; Count < 10; Count++)
    // // 	data_buffer[Count] = 0x80 + Count;
    // // bcm2835_spi_transfern(&data_buffer[0], 10);			//data_buffer used for tx and rx
    //
    // //Return SPI pins to default inputs state
    // bcm2835_spi_end();
    // bcm2835_close();
}
