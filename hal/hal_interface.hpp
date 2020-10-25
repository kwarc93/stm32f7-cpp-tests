/*
 * hal_interface.hpp
 *
 *  Created on: 21 paź 2020
 *      Author: kwarc
 */

#ifndef HAL_INTERFACE_HPP_
#define HAL_INTERFACE_HPP_

#include <cstddef>

namespace hal::interface
{
    class io
    {
    public:
        virtual ~io() {};
        virtual std::byte read(void) = 0;
        virtual void write(std::byte byte) = 0;
        virtual std::size_t read(std::byte *data, std::size_t size) = 0;
        virtual std::size_t write(const std::byte *data, std::size_t size) = 0;
    };

    class temperature_sensor
    {
    public:
        virtual ~temperature_sensor() {};
        virtual float read_temperature(void) = 0;
    };
}

#endif /* HAL_INTERFACE_HPP_ */