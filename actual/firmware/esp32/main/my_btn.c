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
 * @brief Interrupt for Switch Page Loop button
 *
 * @param arg
 */
static void btn_pageLoop_handler(void *arg){
    (void) arg;

    if(pageSWable){
        if(pageNum==PAGE_MAX){pageNum=PAGE_HOME;}
        else{pageNum++;}
    }
}

/**
 * @brief Start Button Interrupt
 *
 */
void my_btnInit(void){
	gpio_config_t btn_conf;

	btn_conf.intr_type = GPIO_INTR_NEGEDGE;
	btn_conf.pin_bit_mask = PAGE_BUTTON_IN;
	btn_conf.pull_up_en = GPIO_PULLUP_ENABLE; // Should also externally pulled up
    btn_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&btn_conf);

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(BUTTON_PAGE_LOOP, btn_pageLoop_handler, NULL);
}

/** @} */
