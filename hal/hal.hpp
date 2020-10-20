/*
 * hal.hpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#ifndef HAL_HPP_
#define HAL_HPP_

#include <cmsis/stm32f7xx.h>

namespace hal
{
    static constexpr uint32_t hsi_clock = 16000000;
    static constexpr uint32_t hse_clock = 25000000;
    static constexpr uint32_t system_clock = 16000000;
    static constexpr uint32_t systick_freq = 1000;

    static constexpr char led1_port = 'I';
    static constexpr uint8_t led1_pin = 1;

    static constexpr char lcd_bkl_port = 'K';
    static constexpr uint8_t lcd_bkl_pin = 3;

    void system_init(void);
}


#endif /* HAL_HPP_ */
