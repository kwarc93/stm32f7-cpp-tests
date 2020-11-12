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
#include <drivers/stm32f7/rcc.hpp>

using namespace drivers;

struct usart_hw_descriptor
{
    USART_TypeDef *const peripheral;
    rcc::periph_bus bus;
    gpio::io tx_pin;
    gpio::io rx_pin;
};

static const usart_hw_descriptor usartx[3] =
{
    [static_cast<uint8_t>(usart::id::usart1)] = {USART1, RCC_PERIPH_BUS(APB2, USART1), { gpio::port::porta, gpio::pin::pin9 }, { gpio::port::portb, gpio::pin::pin7 }},
    /* TODO */
};

usart::usart(id id, uint32_t baudrate) : hw_id (static_cast<uint8_t>(id))
{

    usartx[this->hw_id].peripheral->BRR = (uint32_t) (hal::system::system_clock + baudrate / 2) / baudrate;
    usartx[this->hw_id].peripheral->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

std::byte usart::read()
{
    while (!( usartx[this->hw_id].peripheral->ISR & USART_ISR_RXNE));
    return static_cast<std::byte>(usartx[this->hw_id].peripheral->RDR);
}

void usart::write(std::byte byte)
{
    while (!( usartx[this->hw_id].peripheral->ISR & USART_ISR_TXE));
    usartx[this->hw_id].peripheral->TDR = std::to_integer<volatile uint32_t>(byte);
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

