/*
 * main.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: kwarc
 */

#include <iostream>
#include <iomanip>

#include <hal/hal_system.hpp>
#include <hal/hal_delay.hpp>
#include <hal/hal_led.hpp>
#include <hal/hal_temperature_sensor.hpp>

int main(void)
{
    hal::system::init();

    std::cout << "System started" << std::endl;

    hal::led *debug_led = new hal::leds::debug();
    hal::led *backlight_led = new hal::leds::backlight();

    hal::temperature_sensor *external_sensor = new hal::external_temperature_sensor();
    hal::temperature_sensor *internal_sensor = new hal::internal_temperature_sensor();

    bool led_state = true;
    while (true)
    {
        float external_temperature = external_sensor->read_temperature();
        float internal_temperature = internal_sensor->read_temperature();

        std::cout << "Temperature: "
                  << "internal: " << internal_temperature << "*C"
                  << " external: " << external_temperature << "*C" << std::endl;

        debug_led->set(led_state ^= true);
        hal::delay::delay_ms(500);
    }

    return 0;
}

