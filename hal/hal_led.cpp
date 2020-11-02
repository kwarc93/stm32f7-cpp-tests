/*
 * hal_led.cpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#include "hal_led.hpp"

using namespace hal;

led::led(hal::interface::led *interface)
{
    this->interface = interface;
    this->brightness = 0;
}

led::~led(void)
{
    delete this->interface;
}

void led::set(uint8_t brightness)
{
    this->brightness = brightness;
    this->interface->set(brightness);
}

void led::set(bool state)
{
    uint8_t brightness = state ? 255 : 0;
    this->set(brightness);
}

//---------------------------------------------------------------------------

rgb_led::rgb_led(hal::interface::led *interface[3])
{
    this->r = new led(interface[0]);
    this->g = new led(interface[1]);
    this->b = new led(interface[2]);
}

void rgb_led::set(uint8_t r, uint8_t g, uint8_t b)
{
    this->r->set(r);
    this->g->set(g);
    this->b->set(b);
}

void rgb_led::set(bool r, bool g, bool b)
{
    this->r->set(r);
    this->g->set(g);
    this->b->set(b);
}


