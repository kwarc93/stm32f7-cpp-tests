/*
 * hal_usart.cpp
 *
 *  Created on: 24 paź 2020
 *      Author: kwarc
 */

#include "hal_usart.hpp"

#include <drivers/stm32f7/usart.hpp>

hal::interface::io & hal::usart::debug::get_instance(void)
{
    static drivers::usart usart1 {1, 115200};
    return usart1;
}