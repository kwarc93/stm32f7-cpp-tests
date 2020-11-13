/*
 * gpio.cpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#include "gpio.hpp"

#include <cstdint>

using namespace drivers;

//-----------------------------------------------------------------------------
/* private */

void gpio::enable_clock(port port)
{
    switch (port)
    {
        case port::porta:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
            break;
        case port::portb:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
            break;
        case port::portc:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
            break;
        case port::portd:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
            break;
        case port::porte:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
            break;
        case port::portf:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
            break;
        case port::portg:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
            break;
        case port::porth:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
            break;
        case port::porti:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
            break;
        case port::portj:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
            break;
        case port::portk:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
            break;
        default:
            break;
    }
}

//-----------------------------------------------------------------------------
/* public */

void gpio::init(const io &io, af af, mode mode, type type, speed speed, pupd pupd)
{
    enable_clock(io.port);

    GPIO_TypeDef *port = reinterpret_cast<GPIO_TypeDef *> (io.port);
    uint8_t pin = static_cast<uint8_t> (io.pin);

    port->MODER &= ~(0b11 << (2 * pin));
    port->MODER |= (uint8_t (mode) << (2 * pin));

    port->OTYPER &= ~(0b1 << pin);
    port->OTYPER |= (uint8_t (type) << (pin));

    port->OSPEEDR &= ~(0b11 << (2 * pin));
    port->OSPEEDR |= (uint8_t (speed) << (2 * pin));

    port->PUPDR &= ~(0b11 << (2 * pin));
    port->PUPDR |= (uint8_t (pupd) << (2 * pin));

    port->AFR[pin < 8 ? 0 : 1] &= ~(0b1111 << (4 * (pin - (pin < 8 ? 0 : 8))));
    port->AFR[pin < 8 ? 0 : 1] |= (uint8_t (af) << (4 * (pin - (pin < 8 ? 0 : 8))));
}

bool gpio::read(const io &io)
{
    GPIO_TypeDef *port = reinterpret_cast<GPIO_TypeDef *> (io.port);
    uint8_t pin = static_cast<uint8_t> (io.pin);
    return (port->IDR & (1 << pin));
}

void gpio::write(const io &io, bool state)
{
    GPIO_TypeDef *port = reinterpret_cast<GPIO_TypeDef *> (io.port);
    uint8_t pin = static_cast<uint8_t> (io.pin);
    port->BSRR = state ? (1 << pin) : (1 << pin) << 16;
}

void gpio::toggle(const io &io)
{
    GPIO_TypeDef *port = reinterpret_cast<GPIO_TypeDef *> (io.port);
    uint8_t pin = static_cast<uint8_t> (io.pin);
    port->ODR ^= 1 << pin;
}

