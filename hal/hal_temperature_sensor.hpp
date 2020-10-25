/*
 * hal_temperature_sensor.hpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#ifndef HAL_TEMPERATURE_SENSOR_HPP_
#define HAL_TEMPERATURE_SENSOR_HPP_

#include <hal/hal_interface.hpp>

#include <drivers/ds18b20.hpp>

namespace hal
{
    class temperature_sensor
    {
    public:

        virtual ~temperature_sensor(void)
        {
            delete interface;
        }

        virtual float read_temperature(void)
        {
            return interface->read_temperature();
        }

    protected:
        hal::interface::temperature_sensor *interface;
    };

    class ds18b20 : public temperature_sensor
    {
    public:
        ds18b20(void)
        {
            interface = new drivers::ds18b20(drivers::gpio::port::C, 7);
        }
    };
}

#endif /* HAL_TEMPERATURE_SENSOR_HPP_ */
