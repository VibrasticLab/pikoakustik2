/**
 * @file my_adc.h
 * @brief ADC subsystem header
 *
 * @addtogroup Battery
 * @{
 */

#ifndef _MY_ADC_H_
#define _MY_ADC_H_

#define ADC_REFF_VAL	1020

void my_adcInit(void);
void my_adcValue(void);
void my_adcGetBatt(void);

#endif

 /** @} */
