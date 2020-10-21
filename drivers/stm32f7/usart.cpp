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

usart1::usart1(unsigned int baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    __DSB();

    gpio::init(gpio::port::A, 9, gpio::af::af7, gpio::mode::af);
    gpio::init(gpio::port::B, 7, gpio::af::af7, gpio::mode::af);

    USART1->BRR = (uint32_t) (hal::system::system_clock + baudrate / 2) / baudrate;
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

std::byte usart1::read()
{
    while (!( USART1->ISR & USART_ISR_RXNE));
    return static_cast<std::byte>(USART1->RDR);
}

void usart1::write(std::byte byte)
{
    while (!( USART1->ISR & USART_ISR_TXE));
    USART1->TDR = std::to_integer<volatile uint32_t>(byte);
}

