/*
 * usart.hpp
 *
 *  Created on: 20 paź 2020
 *      Author: kwarc
 */

#ifndef STM32F7_USART_HPP_
#define STM32F7_USART_HPP_

bool usart1_init(unsigned int baudrate);
char usart1_read(void);
void usart1_write(char data);

#endif /* STM32F7_USART_HPP_ */
