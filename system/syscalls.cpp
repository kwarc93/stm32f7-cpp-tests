/*
 * syscalls.c
 *
 *  Created on: 19 paź 2020
 *      Author: kwarc
 */

#include <drivers/stm32f7/usart.hpp>

extern "C" int _write (int fd, char *ptr, int len)
{
    int written = 0;

    while (len--)
    {
        usart1_write(*ptr++);
        written++;
    }

    return written;
}

extern "C" int _read (int fd, char *ptr, int len)
{
    int read = 0;

    while (len--)
    {
        *ptr++ = usart1_read();
        read++;
    }

    return read;
}

extern "C" void _ttywrch(int ch)
{
    usart1_write(ch);
}
