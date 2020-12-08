/*
 * main.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: kwarc
 */

#include <iostream>
#include <functional>
#include <cmath>

#include <hal/hal_system.hpp>
#include <hal/hal_delay.hpp>
#include <hal/hal_led.hpp>
#include <hal/hal_temperature_sensor.hpp>

#include <drivers/stm32f7/core.hpp>

#include <libs/hsluv.h>

static void hsv2rgb(float h, float s, float v, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (h > 360.0f || h < 0.0f || s > 1.0f || s < 0.0f || v > 1.0f || v < 0.0f)
        return;

    /* Convert HSV to RGB */
    auto k = [ &h ](float n) { return fmod((n + h / 60.0f), 6); };
    auto f = [ &k, &s, &v ](float n) { return v - v * s * fmax(0, fmin(fmin(k(n), 4 - k(n)), 1)); };

    *r = f(5) * UINT8_MAX;
    *g = f(3) * UINT8_MAX;
    *b = f(1) * UINT8_MAX;
}

static void rainbow(hal::led_chain *chain)
{
    static float hoffset = 0;
    const float hstep = 360.0f / chain->colors.size();

    for (uint32_t i = 0; i < chain->colors.size(); i++)
    {
        float h = fmod(hoffset + (hstep * (2 * i + 1)) / 2, 360);

        uint8_t r = 0, g = 0, b = 0;
        hsv2rgb(h, 1.0f, 0.5f, &r, &g, &b);

        chain->colors[i] = {g, r, b};
    }

    hoffset += 2;

    drivers::core_critical_section cs;
    chain->update();
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
    auto rgb_led = new hal::leds::basic_rgb();
    auto rgb_strip = new hal::leds::rgb_strip();

    auto external_sensor = new hal::external_temperature_sensor();
    auto internal_sensor = new hal::internal_temperature_sensor();

    backlight_led->set(false);
    debug_led->set(true);

    while (true)
    {
        rainbow(rgb_strip);
    }

    debug_led->set(false);

    return 0;
}

