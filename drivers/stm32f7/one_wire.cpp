/*
 * one_wire.cpp
 *
 *  Created on: 24 paź 2020
 *      Author: kwarc
 */

#include "one_wire.hpp"

#include <drivers/stm32f7/delay.hpp>

using namespace drivers;

//-----------------------------------------------------------------------------
/* public */

one_wire::one_wire(gpio::port port, uint8_t pin)
{
    this->port = port;
    this->pin = pin;

    gpio::init(this->port, this->pin, gpio::af::af0,
               gpio::mode::output, gpio::type::od,
               gpio::speed::very_high, gpio::pupd::pu);
}

bool one_wire::reset_pulse(void)
{
    this->write_data_pin(false);
    delay::delay_us(480);
    this->write_data_pin(true);
    delay::delay_us(70);

    bool presence_impulse = !this->read_data_pin();

    delay::delay_us(410);

    return presence_impulse;
}

std::byte one_wire::read(void)
{
    std::byte byte {0};

    for (uint8_t cnt = 0; cnt < 8; cnt++)
    {
        if (this->read_bit())
            byte |= static_cast<std::byte>(1 << cnt);
    }

    return byte;
}

void one_wire::write(std::byte byte)
{
    for (uint8_t cnt = 0; cnt < 8; cnt++)
    {
        uint8_t bit = static_cast<uint8_t>(byte >> cnt);
        bit &= 1;
        this->write_bit(bit);
    }
}

std::size_t one_wire::read(std::byte *data, std::size_t size)
{
    std::size_t bytes_read = 0;

    while (size--)
    {
        *data++ = this->read();
        bytes_read++;
    }

    return bytes_read;
}

std::size_t one_wire::write(const std::byte *data, std::size_t size)
{
    std::size_t bytes_written = 0;

    while (size--)
    {
        this->write(*data++);
        bytes_written++;
    }

    return bytes_written;
}

//-----------------------------------------------------------------------------
/* private */

void one_wire::write_data_pin(bool state)
{
    gpio::write(this->port, this->pin, state);
}

bool one_wire::read_data_pin(void)
{
    return gpio::read(this->port, this->pin);
}

void one_wire::write_bit(bool bit)
{
    if (bit)
    {
        write_data_pin(false);
        delay::delay_us(6);
        write_data_pin(true);
        delay::delay_us(64);
    }
    else
    {
        write_data_pin(false);
        delay::delay_us(60);
        write_data_pin(true);
        delay::delay_us(10);
    }
}

bool one_wire::read_bit(void)
{
    write_data_pin(false);
    delay::delay_us(6);
    write_data_pin(true);
    delay::delay_us(9);

    bool bit = !read_data_pin();

    delay::delay_us(55);
    return bit;
}
