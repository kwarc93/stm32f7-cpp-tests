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

namespace hal
{

//---------------------------------------------------------------------------

    class led
    {
    public:
        led(hal::interface::led *interface);
        virtual ~led(void);
        virtual void set(uint8_t brightness);
        virtual void set(bool state);
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
        void set(uint8_t r, uint8_t g, uint8_t b);
        void set(bool r, bool g, bool b);
        void set(float hue, float saturation, float value);
    private:
        led *r, *g, *b;
    };

//-----------------------------------------------------------------------------

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

    class simple_rgb : public rgb_led
    {
    public:
        simple_rgb(void) : rgb_led(interface) {}
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

        const std::array<hal::interface::led *, 3> interface = { &rpwm_drv, &gpwm_drv, &bpwm_drv };
    };
}

//---------------------------------------------------------------------------

}

#endif /* HAL_LED_HPP_ */
