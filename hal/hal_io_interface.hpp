/*
 * hal_io_interface.hpp
 *
 *  Created on: 21 paź 2020
 *      Author: kwarc
 */

#ifndef HAL_IO_INTERFACE_HPP_
#define HAL_IO_INTERFACE_HPP_

#include <cstddef>

namespace hal::interface
{
    class io
    {
    public:
        virtual ~io() {};
        virtual std::byte read(void) = 0;
        virtual void write(std::byte) = 0;
    };
}

#endif /* HAL_IO_INTERFACE_HPP_ */
