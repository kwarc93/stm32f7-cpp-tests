/*
 * main.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: kwarc
 */

#include <iostream>
#include <cstring>

#include <hal/hal_system.hpp>

#include <drivers/stm32f7/gpio.hpp>

int main(void)
{
    hal::system::init();

    std::cout << "Enabling green LED..." << std::endl;

    drivers::gpio::init(drivers::gpio::port::I, 1);
    drivers::gpio::write(drivers::gpio::port::I, 1, true);

    std::cout << "Entering infinite loop..." << std::endl;

    while(true);
    return 0;
}

