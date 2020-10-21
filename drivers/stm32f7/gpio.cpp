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
        case port::A:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
            break;
        case port::B:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
            break;
        case port::C:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
            break;
        case port::D:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
            break;
        case port::E:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
            break;
        case port::F:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
            break;
        case port::G:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
            break;
        case port::H:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
            break;
        case port::I:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
            break;
        case port::J:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOJEN;
            break;
        case port::K:
            RCC->AHB1ENR |= RCC_AHB1ENR_GPIOKEN;
            break;
        default:
            break;
    }
}

//-----------------------------------------------------------------------------
/* public */

void gpio::init(port port, uint8_t pin, af af, mode mode, type type, speed speed, pupd pupd)
{
    enable_clock(port);

    GPIO_TypeDef *portp = reinterpret_cast<GPIO_TypeDef *>(port);

    portp->MODER &= ~(0b11 << (2 * pin));
    portp->MODER |= (uint8_t (mode) << (2 * pin));

    portp->OTYPER &= ~(0b1 << pin);
    portp->OTYPER |= (uint8_t (type) << (pin));

    portp->OSPEEDR &= ~(0b11 << (2 * pin));
    portp->OSPEEDR |= (uint8_t (speed) << (2 * pin));

    portp->PUPDR &= ~(0b11 << (2 * pin));
    portp->PUPDR |= (uint8_t (pupd) << (2 * pin));

    portp->AFR[pin < 8 ? 0 : 1] &= ~(0b1111 << (4 * (pin - (pin < 8 ? 0 : 8))));
    portp->AFR[pin < 8 ? 0 : 1] |= (uint8_t (af) << (4 * (pin - (pin < 8 ? 0 : 8))));
}

bool gpio::read(port port, uint8_t pin)
{
    GPIO_TypeDef *portp = reinterpret_cast<GPIO_TypeDef *>(port);
    return (portp->IDR & (1 << pin));
}

void gpio::write(port port, uint8_t pin, bool state)
{
    GPIO_TypeDef *portp = reinterpret_cast<GPIO_TypeDef *>(port);
    portp->BSRR = state ? (1 << pin) : (1 << pin) << 16;
}

void gpio::toggle(port port, uint8_t pin)
{
    GPIO_TypeDef *portp = reinterpret_cast<GPIO_TypeDef *>(port);
    portp->ODR ^= 1 << pin;
}

