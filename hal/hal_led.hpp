/*
 * hal_led.hpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#ifndef HAL_LED_HPP_
#define HAL_LED_HPP_

#include <array>

#include <hal/hal_interface.hpp>

#include <drivers/led_gpio.hpp>
#include <drivers/led_pwm.hpp>
#include <drivers/led_sk6812.hpp>

namespace hal
{

//---------------------------------------------------------------------------

    class led
    {
    public:
        led(hal::interface::led *interface);
        virtual ~led();
        void set(uint8_t brightness);
        void set(bool state);
    protected:
        hal::interface::led *interface;
    private:
        uint8_t brightness;
    };

//-----------------------------------------------------------------------------

    class rgb_led
    {
    public:
        rgb_led(const std::array<hal::interface::led *, 3> &interface);
        virtual ~rgb_led();
        void set(uint8_t r, uint8_t g, uint8_t b);
        void set(bool r, bool g, bool b);
        void set(float hue, float saturation, float value);
    private:
        led *r, *g, *b;
    };

//-----------------------------------------------------------------------------

    class led_chain
    {
    public:
        led_chain(uint32_t leds, uint8_t colors, hal::interface::led *interface);
        virtual ~led_chain();
        void update(void);

        std::vector<std::vector<uint8_t>> colors;
    private:
        const uint32_t led_count;
        const uint8_t led_colors;
        led *leds;
    };

//-----------------------------------------------------------------------------

namespace leds
{
    class debug : public led
    {
    public:
        debug(void) : led {&drv} {}
    private:
        const drivers::gpio::io io = { drivers::gpio::port::porti, drivers::gpio::pin::pin1 };
        drivers::led_gpio drv {io};
    };

    class backlight : public led
    {
    public:
        backlight(void) : led {&drv} {}
    private:
        const drivers::gpio::io io = { drivers::gpio::port::portk, drivers::gpio::pin::pin3 };
        drivers::led_gpio drv {io};
    };

    class basic_rgb : public rgb_led
    {
    public:
        basic_rgb(void) : rgb_led {drv} {}
    private:
        const std::vector<drivers::timer::channel> rch = { drivers::timer::channel::ch1 };
        drivers::pwm rpwm = { drivers::timer::id::timer2, rch, 1000, 0 };
        drivers::led_pwm rpwm_drv {rpwm};

        const std::vector<drivers::timer::channel> gch = { drivers::timer::channel::ch1 };
        drivers::pwm gpwm = { drivers::timer::id::timer3, gch, 1000, 0 };
        drivers::led_pwm gpwm_drv {gpwm};

        const std::vector<drivers::timer::channel> bch = { drivers::timer::channel::ch1 };
        drivers::pwm bpwm = { drivers::timer::id::timer12, bch, 1000, 0 };
        drivers::led_pwm bpwm_drv {bpwm};

        const std::array<hal::interface::led *, 3> drv = { &rpwm_drv, &gpwm_drv, &bpwm_drv };
    };

    class rgb_strip : public led_chain
    {
    public:
        rgb_strip(void) : led_chain {60, 3, &drv} {}
    private:
        const drivers::gpio::io io = { drivers::gpio::port::porti, drivers::gpio::pin::pin2 };
        drivers::led_sk6812 drv {io, 60, 3};
    };
}

//---------------------------------------------------------------------------

}

#endif /* HAL_LED_HPP_ */
