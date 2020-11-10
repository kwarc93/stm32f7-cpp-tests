/*
 * usart.cpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#include "usart.hpp"

#include <cmsis/stm32f7xx.h>

#include <hal/hal_system.hpp>
#include <drivers/stm32f7/gpio.hpp>

using namespace drivers;

static USART_TypeDef * const usartx[3] = { USART1, USART2, USART3 };

usart::usart(id id, uint32_t baudrate) : hw_id (static_cast<uint8_t>(id))
{
    switch (id)
    {
        case id::usart1:
        {
            RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
            __DSB ();
            gpio::io tx { gpio::port::porta, gpio::pin::pin9 };
            gpio::io rx { gpio::port::portb, gpio::pin::pin7 };
            gpio::init (tx, gpio::af::af7, gpio::mode::af);
            gpio::init (rx, gpio::af::af7, gpio::mode::af);
        }
            break;
        case id::usart2:
            RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
            __DSB ();
            /* TODO: Initialize GPIO */
            break;
        case id::usart3:
            RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
            __DSB ();
            /* TODO: Initialize GPIO */
            break;
        default:
            return;
    }

    usartx[this->hw_id]->BRR = (uint32_t) (hal::system::system_clock + baudrate / 2) / baudrate;
    usartx[this->hw_id]->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

std::byte usart::read()
{
    while (!( usartx[this->hw_id]->ISR & USART_ISR_RXNE));
    return static_cast<std::byte>(usartx[this->hw_id]->RDR);
}

void usart::write(std::byte byte)
{
    while (!( usartx[this->hw_id]->ISR & USART_ISR_TXE));
    usartx[this->hw_id]->TDR = std::to_integer<volatile uint32_t>(byte);
}

std::size_t usart::read(std::byte *data, std::size_t size)
{
    std::size_t bytes_read = 0;

    while (size--)
    {
        *data++ = this->read();
        bytes_read++;
    }

    return bytes_read;
}

std::size_t usart::write(const std::byte *data, std::size_t size)
{
    std::size_t bytes_written = 0;

    while (size--)
    {
        this->write(*data++);
        bytes_written++;
    }

    return bytes_written;
}

