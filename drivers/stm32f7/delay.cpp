/*
 * delay.cpp
 *
 *  Created on: 24 paź 2020
 *      Author: kwarc
 */

#include "delay.hpp"

#include <cmsis/stm32f7xx.h>

#include <hal/hal_system.hpp>

using namespace drivers;

void delay::delay_ms(uint32_t ms)
{
    const uint32_t start = DWT->CYCCNT;
    ms *= (hal::system::system_clock / 1000ul);
    while ((DWT->CYCCNT - start) <= ms);
}

void delay::delay_us(uint32_t us)
{
    const uint32_t start = DWT->CYCCNT;
    us *= (hal::system::system_clock / 1000000ul);
    while ((DWT->CYCCNT - start) <= us);
}

