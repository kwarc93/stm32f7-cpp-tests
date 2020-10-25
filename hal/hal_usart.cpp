/*
 * hal_usart.cpp
 *
 *  Created on: 24 paź 2020
 *      Author: kwarc
 */

#include "hal_usart.hpp"

#include <drivers/stm32f7/usart.hpp>

using namespace hal::usart;

hal::interface::io & debug::get_instance(void)
{
    static drivers::usart usart1 {1, 115200};
    return usart1;
}
