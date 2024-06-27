/*  Main file for the hydroponics controller logic

    This file is part of hydroponics-controller.

    hydroponics-controller is free software: you can redistribute it and/or modify it under the terms of the GNU General 
    Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any 
    later version.

    hydroponics-controller is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the 
    implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for more 
    details.

    You should have received a copy of the GNU General Public License along with hydroponics-controller. If not, see 
    <https://www.gnu.org/licenses/>. 
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "relay.h"
#include "water_level.h"

static uint8_t pumpState = 0;

void app_main(void)
{
    relaySetup();
    setupWaterSwitches();

    while(1) {
        uint8_t tankState = shouldTankBeRefilled();
        if (pumpState != tankState) {
            pumpState = tankState;
            relaySet(pumpState);
        }
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
}