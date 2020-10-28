/*
 * core.hpp
 *
 *  Created on: 28 paź 2020
 *      Author: kwarc
 */

#ifndef STM32F7_CORE_HPP_
#define STM32F7_CORE_HPP_

#include <hal/hal_interface.hpp>

namespace drivers
{

class core final
{
public:
    core() = delete;

    static void enable_cycles_counter(void);
};

class core_temperature_sensor : public hal::interface::temperature_sensor
{
public:
    explicit core_temperature_sensor(void);
    float read_temperature(void);
};

}

#endif /* STM32F7_CORE_HPP_ */
