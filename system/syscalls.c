/*
 * syscalls.c
 *
 *  Created on: 19 paź 2020
 *      Author: kwarc
 */


int _write (int fd, char *ptr, int len)
{
  /* Write "len" of char from "ptr" to file id "fd"
   * Return number of char written.
   * Need implementing with UART here. */
  return len;
}

int _read (int fd, char *ptr, int len)
{
  /* Read "len" of char to "ptr" from file id "fd"
   * Return number of char read.
   * Need implementing with UART here. */
  return len;
}

void _ttywrch(int ch)
{
  /* Write one char "ch" to the default console
   * Need implementing with UART here. */
}
