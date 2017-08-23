/*
 * ltc2440.c

 *
 *  Created on: 7 Jul 2017
 *      Author: Lukas Martisiunas
 *
 */
#include "ltc2440.h"
#include "Arduino.h"
#include "SPI.h"

long unsigned int SpiRead(void) {

  long result = 0;
  long b;
  char slaveSelectPin = slave_pin_ADC;
  //  long result2 = 0;// MOSI/SDI pin 7 HIGH => 7 Hz, best resolution
  digitalWrite(slaveSelectPin, LOW);  // take the SS pin low to select the chip
  delayMicroseconds(10);              // probably not needed, only need 25 nsec delay

  b = SPI.transfer(0xff);   // B3
  if (b>>4 != 0b0010){
    digitalWrite(slaveSelectPin,HIGH);
    Serial.println(b,BIN);
     return(0);
}
  result = b << 8;
  //   Serial.println(b,BIN);
  b = SPI.transfer(0xff);   // B2
  result |= b;
  result = result << 8;
  //  Serial.println(b,BIN);
  b = SPI.transfer(0xff);   // B1
  result |= b;
  result = result << 8;
  // Serial.println(b,BIN);
  b = SPI.transfer(0xff);   // B0
  result |= b;
  //  Serial.println(b,BIN);
  // take the SS pin high to de-select the chip:
  digitalWrite(slaveSelectPin, HIGH);

  return (result);
}

long unsigned int  read_ADC() {
  long unsigned int read_adc_val;
  read_adc_val = SpiRead();
  delay(10);
  read_adc_val &= 0x1FFFFFFF; // force high four bits to zero
  read_adc_val = read_adc_val >> 5; // truncate lowest 5 bits
  return read_adc_val;
}

void init_ADC(){

	  SPI.begin(); // initialize SPI, covering MOSI,MISO,SCK signals
	  SPI.setBitOrder(MSBFIRST);  // data is clocked in MSB first
	  SPI.setDataMode(SPI_MODE0);  // SCLK idle low (CPOL=0), MOSI read on rising edge (CPHI=0)
	  SPI.setClockDivider(SPI_CLOCK_DIV32);  // system clock = 16 MHz, chip max = 1 MHz
	  byte temp = slave_pin_ADC;
	  pinMode (temp, OUTPUT);
	  digitalWrite(temp, HIGH); // chip select is active low

	  char temp_2 = SpiRead();
	  temp_2 = SpiRead();
}
