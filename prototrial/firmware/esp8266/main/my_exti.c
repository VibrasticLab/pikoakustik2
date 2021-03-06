#include "my_includes.h"

#define BUTTON_SEL_FILE     9
#define BUTTON_WIFI_SWITCH  12
#define BUTTON_PAGE_SEND    13
#define BUTTON_PAGE_LOOP    14

#define GPIO_INPUT_PIN_SEL  ((1ULL<< BUTTON_WIFI_SWITCH) | \
                               (1ULL<< BUTTON_PAGE_LOOP) | \
                               (1ULL<< BUTTON_PAGE_SEND))

extern bool wifi_ap;
extern uint8_t pageNum;
extern uint8_t sendStep;

bool pageSWable = true;

static void btn_wifi_handler(void *arg){
    (void) arg;

    if(pageNum==PAGE_HOME){
        if(wifi_ap){wifi_ap = false;}
        else{wifi_ap=true;}
    }
}

static void btn_page_loop_handler(void *arg){
    (void) arg;

    if(pageSWable){
        if(pageNum==PAGE_MAX){pageNum=PAGE_HOME;}
        else{pageNum++;}
    }
}

static void btn_page_send_handler(void *arg){
    (void) arg;

    pageNum = PAGE_SEND;
    sendStep = 0;
    pageSWable = false;
}

static void btn_sel_file(void *arg){
    (void) arg;

    if(pageNum!=PAGE_FILES)pageNum = PAGE_FILES;
}

void start_exti(void){
    gpio_config_t io_conf;

    io_conf.intr_type = GPIO_INTR_POSEDGE;
    io_conf.pin_bit_mask = GPIO_INPUT_PIN_SEL;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pull_up_en = GPIO_PULLUP_ENABLE;
    gpio_config(&io_conf);

    gpio_install_isr_service(0);
    gpio_isr_handler_add(BUTTON_WIFI_SWITCH, btn_wifi_handler, NULL);
    gpio_isr_handler_add(BUTTON_PAGE_LOOP, btn_page_loop_handler, NULL);
    gpio_isr_handler_add(BUTTON_PAGE_SEND, btn_page_send_handler, NULL);
    gpio_isr_handler_add(BUTTON_SEL_FILE, btn_sel_file, NULL);
}
