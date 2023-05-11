/**
 * @file my_btn.c
 * @brief GPIO Button code
 *
 * @addtogroup GPIO
 * @{
 */

#include "my_includes.h"

extern uint8_t pageNum;
extern uint8_t my_wifi_type;

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
  uint8_t btnlock_ActA = 0;
  uint8_t btnlock_ActB = 0;


  while (1){
    vTaskDelay(100 / portTICK_PERIOD_MS);

	// page loop button
    if(gpio_get_level(BUTTON_PAGE_LOOP)==0){
		if(btnlock_Page==0){
			btnlock_Page=1;

			if(pageSWable){
				if(pageNum==PAGE_MAX){pageNum=PAGE_HOME;}
				else{pageNum++;}

                if(pageNum==PAGE_PTA) my_ptaArrayReset();
			}
		}
	}
    else if(gpio_get_level(BUTTON_PAGE_LOOP)==1){
		if(btnlock_Page==1) btnlock_Page=0;
	}

	// BUTTON_ACT_X
    if(gpio_get_level(BUTTON_ACT_X)==0){
		if(btnlock_ActA==0){
			btnlock_ActA=1;
		}
	}
    else if(gpio_get_level(BUTTON_ACT_X)==1){
		if(btnlock_ActA==1) btnlock_ActA=0;
	}

    // BUTTON_ACT_Y
    if(gpio_get_level(BUTTON_ACT_Y)==0){
		if(btnlock_ActB==0){
			btnlock_ActB=1;

            if(pageNum==PAGE_HOME){
                // Serial to STM32 Test using LED

                gpio_reset_pin(MY_LED_GPIO);
                gpio_set_direction(MY_LED_GPIO, GPIO_MODE_OUTPUT);
                gpio_set_level(MY_LED_GPIO, 0);

                printf("led 0\r\n");
            }
            else if(pageNum==PAGE_PTA){
                // ASK PTA Array CSV

                printf("pta\r\n");
            }
		}
	}
    else if(gpio_get_level(BUTTON_ACT_Y)==1){
		if(btnlock_ActB==1) btnlock_ActB=0;
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

    xTaskCreate(&btnpageTask, "btnpageTask", 2048, NULL, tskIDLE_PRIORITY, NULL);
}

/** @} */
