/*
 * usart.hpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#ifndef STM32F7_USART_HPP_
#define STM32F7_USART_HPP_

#include <cmsis/stm32f7xx.h>

#include <hal/hal_interface.hpp>

#include <cstdint>

namespace drivers
{

class usart : public hal::interface::io
{
public:
    explicit usart(uint8_t id, uint32_t baudrate);
    virtual ~usart() {};

    std::byte read(void);
    void write(std::byte byte);
    std::size_t read(std::byte *data, std::size_t size);
    std::size_t write(const std::byte *data, std::size_t size);

private:
    uint8_t id;
    static constexpr USART_TypeDef *usartx[3] = { USART1, USART2, USART3 };
};

}

#endif /* STM32F7_USART_HPP_ */
