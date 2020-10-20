/*
 * usart.cpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#include "usart.hpp"

#include <cmsis/stm32f7xx.h>

#include <drivers/stm32f7/gpio.hpp>

bool usart1_init(unsigned int baudrate)
{
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    __DSB();

    gpio::init(gpio::port::A, 9, gpio::af::af7, gpio::mode::af);
    gpio::init(gpio::port::B, 7, gpio::af::af7, gpio::mode::af);

    USART1->BRR = (uint32_t) (16000000 + baudrate / 2) / baudrate;
    USART1->CR1 = USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;

    return true;
}

char usart1_read(void)
{
    while (!( USART1->ISR & USART_ISR_RXNE));
    return USART1->RDR;
}

void usart1_write(char data)
{
    while (!( USART1->ISR & USART_ISR_TXE));
    USART1->TDR = data;
}


