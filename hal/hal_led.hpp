/*
 * hal_led.hpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#ifndef HAL_LED_HPP_
#define HAL_LED_HPP_

#include <hal/hal_interface.hpp>

#include <drivers/led_gpio.hpp>

namespace hal
{

//---------------------------------------------------------------------------

    class led
    {
    public:
        led(hal::interface::led *interface);
        virtual ~led(void);
        void set(uint8_t brightness);
        void set(bool state);
    protected:
        hal::interface::led *interface;
    private:
        uint8_t brightness;
    };

//---------------------------------------------------------------------------

    /* TODO: complete this class */
    class rgb_led
    {
    public:
        rgb_led(hal::interface::led *interface[3]);
        void set(uint8_t r, uint8_t g, uint8_t b);
        void set(bool r, bool g, bool b);
    private:
        led *r, *g, *b;
    };

//---------------------------------------------------------------------------

namespace leds
{
    class debug : public led
    {
    public:
        debug(void) : led(new drivers::led_gpio(io)) {}
    private:
        static constexpr drivers::gpio::io io = { drivers::gpio::port::porti, drivers::gpio::pin::pin1 };
    };

    class backlight : public led
    {
    public:
        backlight(void) : led(new drivers::led_gpio(io)) {}
    private:
        static constexpr drivers::gpio::io io = { drivers::gpio::port::portk, drivers::gpio::pin::pin3 };
    };
}

//---------------------------------------------------------------------------

}

#endif /* HAL_LED_HPP_ */
