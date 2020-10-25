/*
 * delay.hpp
 *
 *  Created on: 24 paź 2020
 *      Author: kwarc
 */

#ifndef STM32F7_DELAY_HPP_
#define STM32F7_DELAY_HPP_

#include <cstdint>

namespace drivers
{
    class delay final
    {
    public:
        delay() = delete;

        static void delay_ms(uint32_t ms);
        static void delay_us(uint32_t us);
    };
}

#endif /* STM32F7_DELAY_HPP_ */
