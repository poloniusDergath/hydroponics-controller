/*  Implementation for the relay control logic

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
#include "relay.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "relay";
static uint8_t relayState = 0;

void relaySetup() {
    ESP_LOGI(TAG, "Relay configured to pin %d", RELAY_GPIO);
    gpio_reset_pin(RELAY_GPIO);
    gpio_set_direction(RELAY_GPIO, GPIO_MODE_OUTPUT);
}

void relayToggle() {
    relayState = !relayState;
    ESP_LOGI(TAG, "Toggling relay to state: %d", relayState);
    gpio_set_level(RELAY_GPIO, relayState);
}

void relaySet(uint8_t level) {
    ESP_LOGI(TAG, "Setting relay to state: %d", level);
    gpio_set_level(RELAY_GPIO, level);
}