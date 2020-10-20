/*
 * gpio.hpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#ifndef STM32F7_GPIO_HPP_
#define STM32F7_GPIO_HPP_

#include <cmsis/stm32f7xx.h>

class gpio final
{
public:
    gpio() = delete;

    enum class port:uint32_t
    {
        A = GPIOA_BASE, B = GPIOB_BASE, C = GPIOC_BASE, D = GPIOD_BASE, E = GPIOE_BASE, F = GPIOF_BASE,
        G = GPIOG_BASE, H = GPIOH_BASE, I = GPIOI_BASE, J = GPIOJ_BASE, K = GPIOK_BASE
    };
    enum class mode:uint8_t
    {
        input = 0b00, output = 0b01, af = 0b10, analog = 0b11
    };
    enum class type:uint8_t
    {
        pp = 0b0, od = 0b1
    };
    enum class speed:uint8_t
    {
        low = 0b00, medium = 0b01, high = 0b10, very_high = 0b11
    };
    enum class pupd:uint8_t
    {
        none = 0b00, pu = 0b01, pd = 0b10
    };

    enum class af:uint8_t
    {
        af0 = 0, af1, af2, af3, af4, af5, af6, af7, af8, af9, af10, af11, af12, af13, af14, af15
    };

    static void init(port port,
                     uint8_t pin,
                     af af = af::af0,
                     mode mode = mode::output,
                     type type = type::pp,
                     speed speed = speed::very_high,
                     pupd pupd = pupd::none);
    static bool read(port port, uint8_t pin);
    static void write(port port, uint8_t pin, bool state);
    static void toggle(port port, uint8_t pin);
private:
    static void enable_clock(port port);
};

#endif /* STM32F7_GPIO_HPP_ */
