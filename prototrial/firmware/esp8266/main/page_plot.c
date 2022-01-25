#include "my_includes.h"

extern ssd1306_t oled_dev;

static uint8_t lcdbuff[DISPLAY_WIDTH * DISPLAY_HEIGHT / 8];

static uint8_t xpoint[] = {10,25,40,55,70,85,100,115};
static uint8_t ypoint[] = {10,30,15,25,30,35,40,50};

static void line_plot(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1){
    ssd1306_draw_line(&oled_dev,lcdbuff, x0,y0,x1,y1, OLED_COLOR_WHITE);
}

void page_plot(void){}

void page_plot_demo(void){
    ssd1306_clear_buffer(lcdbuff,0,sizeof(lcdbuff));

    uint8_t idx;
    for(idx=0;idx<sizeof(xpoint)-1;idx++){
        line_plot(xpoint[idx],ypoint[idx],
                  xpoint[idx+1],ypoint[idx+1]);
    }

    ssd1306_load_frame_buffer(&oled_dev,lcdbuff);
}
