/*
 * hal_led.hpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#ifndef HAL_LED_HPP_
#define HAL_LED_HPP_

namespace hal::led
{
    namespace low_battery
    {
        void init(void);
        void set(bool);
    }

    namespace lcd_backlight
    {
        void init(void);
        void set(bool);
    }
}

#endif /* HAL_LED_HPP_ */
