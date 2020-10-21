/*
 * usart.hpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#ifndef STM32F7_USART_HPP_
#define STM32F7_USART_HPP_

#include <hal/hal_io_interface.hpp>

namespace drivers
{

class usart1 : public hal::interface::io
{
public:
    explicit usart1(unsigned int baudrate);
    virtual ~usart1() {};

    std::byte read(void);
    void write(std::byte);
};

}

#endif /* STM32F7_USART_HPP_ */
