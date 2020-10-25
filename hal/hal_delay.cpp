/*
 * hal_delay.cpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#include "hal_delay.hpp"

#include <drivers/stm32f7/delay.hpp>

using namespace hal::delay;

void hal::delay::delay_ms(unsigned int ms)
{
    drivers::delay::delay_ms(ms);
}

void hal::delay::delay_us(unsigned int us)
{
    drivers::delay::delay_us(us);
}
