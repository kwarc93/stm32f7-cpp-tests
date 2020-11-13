/*
 * main.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: kwarc
 */

#include <iostream>
#include <cmath>

#include <hal/hal_system.hpp>
#include <hal/hal_delay.hpp>
#include <hal/hal_led.hpp>
#include <hal/hal_temperature_sensor.hpp>

#include <libs/hsluv.h>

static void rainbow(hal::leds::simple_rgb *led)
{
    static float x = 0;
    const float tau = acosf(-1.0f) * 2.0f;
    float vect[3] = {0.0f / 3.0f, 2.0f / 3.0f, 1.0f / 3.0f };

    vect[0] += x; vect[1] += x; vect[2] += x;
    vect[0] *= tau; vect[1] *= tau; vect[2] *= tau;
    vect[0] = sinf(vect[0]); vect[1] = sinf(vect[1]); vect[2] = sinf(vect[2]);
    vect[0] *= 0.5f; vect[1] *= 0.5f; vect[2] *= 0.5f;
    vect[0] += 0.5f; vect[1] += 0.5f; vect[2] += 0.5f;
    vect[0] = sqrtf(vect[0]); vect[1] = sqrtf(vect[1]); vect[2] = sqrtf(vect[2]);

    uint8_t rgb[3] = {vect[0] * UINT8_MAX, vect[1] * UINT8_MAX, vect[2] * UINT8_MAX};

    led->set(rgb[0], rgb[1], rgb[2]);

    x += 0.001f;
    if (x >= 1.0)
        x = 0.0f;
}

static void hsluv(hal::leds::simple_rgb *led)
{
    static float h = 0.0f;

    float r, g, b;
    hsluv2rgb(h, 100.0f, 50.0f, &r, &g, &b);

    uint8_t u8r = r * UINT8_MAX;
    uint8_t u8g = g * UINT8_MAX;
    uint8_t u8b = b * UINT8_MAX;
    led->set(u8r, u8g, u8b);

    h += 0.3f;
    if (h >= 360.0f)
        h = 0.0f;
}

static void hsv(hal::leds::simple_rgb *led)
{
    static float h = 0.0f;
    led->set(h, 1.0f, 1.0f);
    h += 0.2f;
    if (h >= 360.0f)
        h = 0.0f;
}

static void temperature(hal::temperature_sensor *int_sens, hal::temperature_sensor *ext_sens)
{
    float ext_temp = ext_sens->read_temperature();
    float int_temp = int_sens->read_temperature();

    std::cout << "Temperature: "
              << "internal: " << int_temp << "*C"
              << " external: " << ext_temp << "*C" << std::endl;
}

int main(void)
{
    hal::system::init();

    std::cout << "System started" << std::endl;

    auto debug_led = new hal::leds::debug();
    auto backlight_led = new hal::leds::backlight();
    auto rgb_led = new hal::leds::simple_rgb();

    auto external_sensor = new hal::external_temperature_sensor();
    auto internal_sensor = new hal::internal_temperature_sensor();

    backlight_led->set(false);
    debug_led->set(true);

    while (true)
    {
        hsv(rgb_led);
        hal::delay::delay_ms(5);
    }

    debug_led->set(false);

    return 0;
}

