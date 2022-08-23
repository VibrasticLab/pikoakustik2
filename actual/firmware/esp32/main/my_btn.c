/**
 * @file my_btn.c
 * @brief GPIO Button code
 *
 * @addtogroup GPIO
 * @{
 */

#include "my_includes.h"

extern uint8_t pageNum;

/**
 * @brief Flag if page switchable or not
 *
 */
bool pageSWable = true;

/**
 * @brief Buton Page Task Loop
 *
 * @param pvParameter
 */
static void btnpageTask(void *pvParameter){
  uint8_t btnlock_Page = 0;

  while (1){
    vTaskDelay(100 / portTICK_PERIOD_MS);

	// page loop button
    if(gpio_get_level(BUTTON_PAGE_LOOP)==0){
		if(btnlock_Page==0){
			btnlock_Page=1;

			if(pageSWable){
				if(pageNum==PAGE_MAX){pageNum=PAGE_HOME;}
				else{pageNum++;}
			}
		}
	}
	else if(gpio_get_level(BUTTON_PAGE_LOOP)==1){
		if(btnlock_Page==1) btnlock_Page=0;
	}

	// end button check loop
  }
}

/**
 * @brief Start Button Interrupt
 *
 */
void my_btnInit(void){
	gpio_config_t btn_conf;

	btn_conf.intr_type = GPIO_INTR_DISABLE;
	btn_conf.mode = GPIO_MODE_INPUT;
	btn_conf.pin_bit_mask = PAGE_BUTTON_IN;
	btn_conf.pull_up_en = GPIO_PULLUP_DISABLE;
    btn_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&btn_conf);

    xTaskCreate(&btnpageTask, "btnpageTask", 1024, NULL, tskIDLE_PRIORITY, NULL);
}

/** @} */