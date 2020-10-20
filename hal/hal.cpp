/*
 * hal.cpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#include "hal.hpp"

#include <drivers/stm32f7/usart.hpp>

void hal::system_init(void)
{
    /* Initialize USART1 for stdout */
    usart1_init(115200);
}
