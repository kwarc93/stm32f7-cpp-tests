/*
 * hal.cpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#include "hal_system.hpp"

#include <hal/hal_usart.hpp>

//-----------------------------------------------------------------------------

static auto &debug = hal::usart::debug::get_instance();

void hal::system::init(void)
{
    /* Number of group priorities: 16, subpriorities: 16. */
    NVIC_SetPriorityGrouping(0x07 - __NVIC_PRIO_BITS);

    /* Set System Tick interrupt */
    SysTick_Config(hal::system::system_clock / hal::system::systick_freq);

    /* Enable DWT cycles counter (TODO: create core driver)*/
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CYCCNT = 0;
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

//-----------------------------------------------------------------------------
/* syscalls */

extern "C" int _write (int fd, char *ptr, int len)
{
    return debug.write(reinterpret_cast<std::byte*>(ptr), len);
}

extern "C" int _read (int fd, char *ptr, int len)
{
    return debug.read(reinterpret_cast<std::byte*>(ptr), len);
}

extern "C" void _ttywrch(int ch)
{
    debug.write(static_cast<std::byte>(ch));
}

extern "C" void SysTick_Handler(void)
{

}
