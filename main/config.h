/*  Configuration parameters for the hydroponics controller

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
#define RELAY_GPIO GPIO_NUM_6
#define WATER_LEVEL_LOW_GPIO GPIO_NUM_20
#define WATER_LEVEL_HIGH_GPIO GPIO_NUM_22
#define WATER_LEVEL_BIT_MASK (1ULL << WATER_LEVEL_HIGH_GPIO | 1ULL << WATER_LEVEL_LOW_GPIO)