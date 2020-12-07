/*
 * led_sk6812.cpp
 *
 *  Created on: 2 gru 2020
 *      Author: kwarc
 */

#include "led_sk6812.hpp"

#include <drivers/stm32f7/delay.hpp>
#include <drivers/stm32f7/core.hpp>

using namespace drivers;

led_sk6812::led_sk6812(gpio::io io, uint32_t leds, uint8_t colors) : led_count(leds), color_count(colors)
{
    this->io = io;
    this->bytes_written = 0;
    gpio::init(this->io,
               gpio::af::af0,
               gpio::mode::output,
               gpio::type::od);

    for (uint32_t i = 0; i < this->led_count; i++)
        for (uint8_t j = 0; j < this->color_count; j++)
            this->set(0);
}

void led_sk6812::set(uint8_t brightness)
{
    for (int8_t cnt = 7; cnt >= 0; cnt--)
    {
        bool bit = brightness & (1 << cnt);
        gpio::write(this->io, true);

        if (bit)
            delay::nop<6>();
        else
            delay::nop<1>();

        gpio::write(this->io, false);
        delay::nop<6>();
    }

    if (++this->bytes_written == (this->led_count * this->color_count))
        this->reset();
}

void led_sk6812::reset(void)
{
    this->bytes_written = 0;
    gpio::write(this->io, false);
    delay::us(80);
}
