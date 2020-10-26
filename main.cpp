/*
 * main.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: kwarc
 */

#include <iostream>
#include <iomanip>

#include <hal/hal_system.hpp>

#include <hal/hal_led.hpp>
#include <hal/hal_delay.hpp>
#include <hal/hal_temperature_sensor.hpp>

int main(void)
{
    hal::system::init();

    std::cout << "System started" << std::endl;

    hal::led::debug::init();
    hal::led::lcd_backlight::init();

    hal::temperature_sensor *sensor = new hal::air_temperature_sensor();

    bool led_state = true;
    while (true)
    {
        float temperature = sensor->read_temperature();

        std::cout << "Temperature: " << temperature << " *C" << std::endl;

        hal::led::debug::set(led_state ^= true);
        hal::delay::delay_ms(500);
    }

    return 0;
}

