/*
 * ds18b20.hpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#ifndef DS18B20_HPP_
#define DS18B20_HPP_

#include <hal/hal_interface.hpp>
#include <drivers/stm32f7/one_wire.hpp>

namespace drivers
{
    class ds18b20 : public hal::interface::temperature_sensor
    {
    public:
        explicit ds18b20(drivers::gpio::port port, uint8_t pin);

        float read_temperature(void);

    private:
    drivers::one_wire one_wire;

    };
}

#endif /* DS18B20_HPP_ */
