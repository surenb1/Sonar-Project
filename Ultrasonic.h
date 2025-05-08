/**
 * @file Ultrasonic.h
 * @brief Header file for ultrasonic sensor driver using Timer Capture on TM4C123GH6PM.
 */

#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>

void Ultrasonic_Init(void);
uint32_t Ultrasonic_Read_Distance(void);

#endif /* ULTRASONIC_H */
