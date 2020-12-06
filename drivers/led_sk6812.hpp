/*
 * led_sk6812.h
 *
 *  Created on: 2 gru 2020
 *      Author: kwarc
 */

#ifndef LED_SK6812_HPP_
#define LED_SK6812_HPP_

#include <hal/hal_interface.hpp>

#include <drivers/stm32f7/gpio.hpp>

namespace drivers
{
    class led_sk6812 : public hal::interface::led
    {
    public:
        led_sk6812(drivers::gpio::io io, uint32_t leds, uint8_t colors);
        void set(uint8_t brightness);
        void reset(void);

    private:
        drivers::gpio::io io;
        const uint32_t led_count;
        const uint8_t color_count;
        uint32_t bytes_written;
    };
}

#endif /* LED_SK6812_HPP_ */
