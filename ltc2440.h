/*
 * ltc2440.h
 *
 *  Created on: 7 Jul 2017
 *      Author: Lukas Martisiunas
 *      Description: Basic library to initialise and use LTC2440 with Arduino
 */

#define ltc2440_h_
#define slave_pin_ADC 10;

long unsigned int SpiRead(void);
long unsigned int  read_ADC();
void init_ADC();


