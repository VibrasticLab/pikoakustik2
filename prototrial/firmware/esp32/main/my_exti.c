/**
 * @file my_exti.c
 * @brief GPIO Interrupt source
 *
 * @addtogroup GPIO
 * @{
 */

#include "my_includes.h"

/**
 * @brief Button Action A pin
 *
 */
#define BUTTON_WIFI_SWITCH  25

/**
 * @brief Button Action B pin
 *
 */
#define BUTTON_PAGE_SEND    26

/**
 * @brief Switch Page Loop pin
 *
 */
#define BUTTON_PAGE_LOOP    27

/**
 * @brief Input GPIO group
 *
 */
#define GPIO_INPUT_PIN_SEL  ((1ULL<< BUTTON_WIFI_SWITCH) | \
                               (1ULL<< BUTTON_PAGE_LOOP) | \
                               (1ULL<< BUTTON_PAGE_SEND))

/**
 * @brief Interrupt Flag number
 *
 */
#define ESP_INTR_FLAG_DEFAULT 0

extern bool wifi_ap;
extern uint8_t pageNum;
extern uint8_t sendStep;

/**
 * @brief Flag if page switchable or not
 *
 */
bool pageSWable = true;

/**
 * @brief Interrupt for Action A button
 *
 * @param arg
 */
static void btn_wifi_handler(void *arg){
    (void) arg;

    if(pageNum==PAGE_HOME){
        if(wifi_ap){wifi_ap = false;}
        else{wifi_ap=true;}
    }
}

/**
 * @brief Interrupt for Switch Page Loop button
 *
 * @param arg
 */
static void btn_page_loop_handler(void *arg){
    (void) arg;

    if(pageSWable){
        if(pageNum==PAGE_MAX){pageNum=PAGE_HOME;}
        else{pageNum++;}
    }
}

/**
 * @brief Interrupt for Action B button
 *
 * @param arg
 */
static void btn_page_send_handler(void *arg){
    (void) arg;

    pageNum = PAGE_SEND;
    pageSWable = false;
    page_send();
}

/**
 * @brief Start GPIO Interrupt
 *
 */
void start_exti(void){
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_NEGEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE; // Should also externally pulled up
    io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(ESP_INTR_FLAG_DEFAULT);
    gpio_isr_handler_add(BUTTON_WIFI_SWITCH, btn_wifi_handler, NULL);
    gpio_isr_handler_add(BUTTON_PAGE_LOOP, btn_page_loop_handler, NULL);
    gpio_isr_handler_add(BUTTON_PAGE_SEND, btn_page_send_handler, NULL);
}

/** @} */
