/*
 * hal.cpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#include "hal_system.hpp"

#include <drivers/stm32f7/usart.hpp>

//-----------------------------------------------------------------------------

/* Initialize USART1 for stdout */
static drivers::usart1 usart1{115200};

void hal::system::init(void)
{
    /* Number of group priorities: 16, subpriorities: 16. */
    NVIC_SetPriorityGrouping(0x07 - __NVIC_PRIO_BITS);

    /* Set System Tick interrupt */
    SysTick_Config(hal::system::system_clock / hal::system::systick_freq);
}

//-----------------------------------------------------------------------------
/* syscalls */

extern "C" int _write (int fd, char *ptr, int len)
{
    int written = 0;

    while (len--)
    {
        usart1.write(static_cast<std::byte>(*ptr++));
        written++;
    }

    return written;
}

extern "C" int _read (int fd, char *ptr, int len)
{
    int read = 0;

    while (len--)
    {
        *ptr++ = static_cast<char>(usart1.read());
        read++;
    }

    return read;
}

extern "C" void _ttywrch(int ch)
{
    usart1.write(static_cast<std::byte>(ch));
}

extern "C" void SysTick_Handler(void)
{

}
