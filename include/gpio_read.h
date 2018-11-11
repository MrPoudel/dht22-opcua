/*Raspberry Pi with WiringPi
 * Author: MrPoudel
 * Version: 0.1.0
 * https://github.com/
 */
#ifndef GPIO_READ_H
#define GPIO_READ_H

#include <wiringPi.h>

extern const unsigned short signal_gpio;
extern unsigned short data[5];

float humidity;
float celsius;
float fahrenheit;
short checksum;


short readData();
void *threadFunc(void* arg);

#endif

