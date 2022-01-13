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
    start_olcd();
    start_blink();
    
    while(true) {
        int loop = loop_console();
        if(loop==1)break;
    }
}