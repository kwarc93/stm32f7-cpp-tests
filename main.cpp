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

    auto debug_led = new hal::leds::debug();
    auto backlight_led = new hal::leds::backlight();
    auto rgb_led = new hal::leds::simple_rgb();

    auto external_sensor = new hal::external_temperature_sensor();
    auto internal_sensor = new hal::internal_temperature_sensor();

    bool led_state = true;
    float hue = 0;
    const float hue_incr = 0.2f;

    while (true)
    {
//        float external_temperature = external_sensor->read_temperature();
//        float internal_temperature = internal_sensor->read_temperature();
//
//        std::cout << "Temperature: "
//                  << "internal: " << internal_temperature << "*C"
//                  << " external: " << external_temperature << "*C" << std::endl;
//
//        debug_led->set(led_state ^= true);

        rgb_led->set(hue, 1.0f, 1.0f);
        hue += hue_incr;
        if (hue > 360.0f)
            hue = 0;
        hal::delay::delay_ms(5);
    }

    return 0;
}

