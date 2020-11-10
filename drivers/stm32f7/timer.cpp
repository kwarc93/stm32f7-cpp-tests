/*
 * timer.cpp
 *
 *  Created on: 10 lis 2020
 *      Author: kwarc
 */

#include "timer.hpp"

#include <cmsis/stm32f7xx.h>

#include <drivers/stm32f7/gpio.hpp>

using namespace drivers;

static TIM_TypeDef * const timerx[3] = { TIM1, TIM2, TIM3 };

timer::timer(id id) : hw_id(static_cast<uint8_t>(id))
{
    /* TODO */
    /* Enable RCC peripheral clock. */
    switch (id)
    {
        case id::timer1:
            RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
            __DSB ();
//            gpio::io tx { gpio::port::porta, gpio::pin::pin9 };
//            gpio::io rx { gpio::port::portb, gpio::pin::pin7 };
//            gpio::init (tx, gpio::af::af7, gpio::mode::af);
//            gpio::init (rx, gpio::af::af7, gpio::mode::af);
            break;

        case id::timer2:
            RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
            __DSB ();
            break;

        case id::timer3:
            RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
            __DSB ();
            break;

        default:
            return;

    }

    /* Enable auto-reload preload and enable timer (upcounting mode). */
    timerx[this->hw_id]->CR1 |= TIM_CR1_ARPE | TIM_CR1_CEN;
}

bool timer::set_frequency(uint32_t frequency)
{
//    uint32_t arr = 1;
//    uint32_t psc = 1;
//
//    /* Clocks from APB1 and APB2 buses that are connected to timers are multiplied internally by two if prescaler is greater than 1. */
//    uint32_t tim_bus_clock = rcc_get_periph_bus_freq(tobj->hw_conf.rcc.bus);
//    if (rcc_get_periph_bus_presc(tobj->hw_conf.rcc.bus) > 1)
//        tim_bus_clock *=2;
//
//    /* Find smallest prescaler value according to specified frequency to achieve best frequency accuracy.
//     * Then calculate auto reload register value and check if it fits into timer resolution. */
//    for (psc = 1; psc < tobj->psc_max_val; psc *= 2)
//    {
//        arr = tim_bus_clock / (psc * frequency);
//        if (arr < tobj->cnt_max_val)
//        {
//            timerx[this->hw_id]->ARR = arr - 1;
//            timerx[this->hw_id]->PSC = psc - 1;
//
//            /* Re-initialize the counter and generate an update of the registers */
//            timerx[this->hw_id]->EGR |= TIM_EGR_UG;
//            return true;
//        }
//    }
//
//    return false;

    /* TODO */
    return true;
}

bool timer::configure_channel(channel ch, channel_mode ch_mode)
{
    /* TODO */
    return true;
}

//-----------------------------------------------------------------------------

counter::counter(id id, mode mode, uint32_t frequency, void (*irq_update_callback)(void)) :
timer(id)
{
    /* TODO */
    this->irq_update_callback = irq_update_callback;
    this->set_frequency(frequency);
}

uint32_t counter::get_value(void)
{
    return timerx[this->hw_id]->CNT;
}

//-----------------------------------------------------------------------------

pwm::pwm(id id, uint32_t frequency, float duty) :
timer(id)
{
    /* TODO */
    this->configure_channel(timer::channel::ch1, timer::channel_mode::pwm);
    this->set_duty(timer::channel::ch1, duty);
    this->set_frequency(frequency);

}

void pwm::set_duty(channel channel, float duty)
{

}
