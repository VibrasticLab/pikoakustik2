/**
 * @file my_adc.h
 * @brief ADC subsystem header
 *
 * @addtogroup Battery
 * @{
 */

#ifndef _MY_ADC_H_
#define _MY_ADC_H_

#define ADC_BATT_EMTY	 840 // 3.4 volt
#define ADC_BATT_FULL	1040 // 4.1 volt

void my_adcInit(void);
void my_adcValue(void);
void my_adcGetBatt(void);

#endif

 /** @} */
