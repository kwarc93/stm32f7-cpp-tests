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

usart::usart(uint8_t id, uint32_t baudrate)
{
    switch (id)
    {
    case 1:
        RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
        __DSB();
        gpio::init(gpio::port::A, 9, gpio::af::af7, gpio::mode::af);
        gpio::init(gpio::port::B, 7, gpio::af::af7, gpio::mode::af);
        break;
    case 2:
        RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
        __DSB();
        /* TODO: Initialize GPIO */
        break;
    case 3:
        RCC->APB1ENR |= RCC_APB1ENR_USART3EN;
        __DSB();
        /* TODO: Initialize GPIO */
        break;
    default:
        return;
    }

    this->id = id;

    this->usartx[this->id]->BRR = (uint32_t) (hal::system::system_clock + baudrate / 2) / baudrate;
    this->usartx[this->id]->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

std::byte usart::read()
{
    while (!( this->usartx[this->id]->ISR & USART_ISR_RXNE));
    return static_cast<std::byte>(this->usartx[this->id]->RDR);
}

void usart::write(std::byte byte)
{
    while (!( this->usartx[this->id]->ISR & USART_ISR_TXE));
    this->usartx[this->id]->TDR = std::to_integer<volatile uint32_t>(byte);
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

