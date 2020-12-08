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

led_sk6812::led_sk6812(gpio::io io, uint32_t leds, uint8_t colors) :
bytes_to_write {leds * colors}
{
    this->io = io;
    this->bytes_written = 0;
    gpio::init(this->io,
                        gpio::af::af0,
                        gpio::mode::output,
                        gpio::type::od);

    for (uint32_t i = 0; i < this->bytes_to_write; i++)
        this->set(0);
}

void led_sk6812::set(uint8_t brightness)
{
    for (int8_t cnt = 7; cnt >= 0; cnt--)
    {
        bool bit = brightness & (1 << cnt);

        if (bit)
        {
            gpio::write(this->io, true);
            delay::clock(50);
            gpio::write(this->io, false);
            delay::clock(10);
        }
        else
        {
            gpio::write(this->io, true);
            delay::clock(10);
            gpio::write(this->io, false);
            delay::clock(50);
        }
    }

    if (++this->bytes_written == this->bytes_to_write)
        this->reset();
}

void led_sk6812::reset(void)
{
    this->bytes_written = 0;
    gpio::write(this->io, false);
    delay::us(80);
}
