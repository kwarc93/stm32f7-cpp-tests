/*
 * usart.hpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#ifndef STM32F7_USART_HPP_
#define STM32F7_USART_HPP_

#include <hal/hal_interface.hpp>

#include <cstdint>

namespace drivers
{

class usart : public hal::interface::serial
{
public:
    enum class id
    {
        usart1, usart2, usart3
    };

    usart(id id, uint32_t baudrate);
    ~usart() {};

    std::byte read(void);
    void write(std::byte byte);
    std::size_t read(std::byte *data, std::size_t size);
    std::size_t write(const std::byte *data, std::size_t size);

private:
    const uint8_t hw_id;
};

}

#endif /* STM32F7_USART_HPP_ */
