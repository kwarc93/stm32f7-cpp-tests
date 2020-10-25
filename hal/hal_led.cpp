/*
 * hal_led.cpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#include "hal_led.hpp"

#include <drivers/stm32f7/gpio.hpp>

using namespace hal::led;

void low_battery::init(void)
{
    drivers::gpio::init(drivers::gpio::port::I, 1);
    drivers::gpio::write(drivers::gpio::port::I, 1, false);
}

void low_battery::set(bool state)
{
    drivers::gpio::write(drivers::gpio::port::I, 1, state);
}

void lcd_backlight::init(void)
{
    drivers::gpio::init(drivers::gpio::port::K, 3);
    drivers::gpio::write(drivers::gpio::port::K, 3, false);
}

void lcd_backlight::set(bool state)
{
    drivers::gpio::write(drivers::gpio::port::K, 3, state);
}

