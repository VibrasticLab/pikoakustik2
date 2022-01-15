/* Console example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include "my_includes.h"

void app_main()
{
    start_console();
    start_ssd1306();
    start_wifiAP();
    start_page();
    start_blink();

    while(true) {
#ifdef CONSOLE_DUMB
        loop_console();
#else
        int loop = loop_console();
        if(loop==1)printf("Empty Command\r\n");
#endif
    }
}
