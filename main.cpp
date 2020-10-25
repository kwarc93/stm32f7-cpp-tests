/*
 * main.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: kwarc
 */

#include <iostream>
#include <iomanip>
#include <cstring>

#include <hal/hal_system.hpp>

#include <drivers/stm32f7/gpio.hpp>
#include <drivers/stm32f7/delay.hpp>

#include <hal/hal_temperature_sensor.hpp>

int main(void)
{
    hal::system::init();

    std::cout << "System started" << std::endl;

    drivers::gpio::init(drivers::gpio::port::I, 1);

    hal::temperature_sensor *temp_sens = new hal::ds18b20();

    while(true)
    {
        float temperature = temp_sens->read_temperature();
        std::cout << "Temperature: " << temperature << " *C" << std::endl;
        drivers::gpio::toggle(drivers::gpio::port::I, 1);
        drivers::delay::delay_ms(500);
    }

    return 0;
}

