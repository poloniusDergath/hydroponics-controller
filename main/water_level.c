/*  Implementations for water level control functions

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
#include "water_level.h"
#include "config.h"
#include "driver/gpio.h"
#include "esp_log.h"

static const char *TAG = "water_level";

static uint8_t highState = 0;
static uint8_t lowState = 0;
static enum WaterState currentState = EMPTYING;

void setupWaterSwitches() {
    ESP_LOGI(TAG, "Switches configured on pins high [%d] and low [%d]", WATER_LEVEL_HIGH_GPIO, WATER_LEVEL_LOW_GPIO);
    gpio_config_t gpioConfig;
    gpioConfig.pin_bit_mask = WATER_LEVEL_BIT_MASK;
    gpioConfig.pull_down_en = GPIO_PULLDOWN_DISABLE;
    gpioConfig.pull_up_en = GPIO_PULLUP_ENABLE;
    gpioConfig.mode = GPIO_MODE_INPUT;
    gpioConfig.intr_type = GPIO_INTR_DISABLE;
    gpio_config(&gpioConfig);
}

uint8_t shouldTankBeRefilled() {
    highState = !gpio_get_level(WATER_LEVEL_HIGH_GPIO);
    lowState = !gpio_get_level(WATER_LEVEL_LOW_GPIO);
    ESP_LOGI(TAG, "highState [%d], lowState [%d]", highState, lowState);

    if (highState && !lowState) {
        ESP_LOGE(TAG, "Something is wrong with the configuration, state should not be possible (high = 1, low = 0)");
        return 0;
    } else if (!highState && lowState) {
        ESP_LOGI(TAG, "Detected level below max, currentState is [%d] (0 = FILLING, 1 = EMPTYING), will return [%d]", 
        currentState, currentState == FILLING);
        return currentState == FILLING;
    } else if (highState && lowState) {
        ESP_LOGI(TAG, "Detected level at max, currentState is [%d] (0 = FILLING, 1 = EMPTYING), will return [0]", 
        currentState);
        currentState = EMPTYING;
        return 0;
    } else {
        ESP_LOGI(TAG, "Detected level below low, currentState is [%d] (0 = FILLING, 1 = EMPTYING), will return [1]", 
        currentState);
        currentState = FILLING;
        return 1;
    }
}