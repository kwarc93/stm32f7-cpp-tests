/*
 * one_wire.hpp
 *
 *  Created on: 24 paź 2020
 *      Author: kwarc
 */

#ifndef STM32F7_ONE_WIRE_HPP_
#define STM32F7_ONE_WIRE_HPP_

#include <hal/hal_interface.hpp>

#include <drivers/stm32f7/gpio.hpp>

#include <cstdint>

namespace drivers
{

class one_wire : public hal::interface::io
{
public:
    explicit one_wire(drivers::gpio::port port, uint8_t pin);
    virtual ~one_wire() {};

    bool reset_pulse(void);
    std::byte read(void);
    void write(std::byte byte);
    std::size_t read(std::byte *data, std::size_t size);
    std::size_t write(const std::byte *data, std::size_t size);

private:
    drivers::gpio::port port;
    uint8_t pin;

    inline void write_data_pin(bool state);
    inline bool read_data_pin(void);
    void write_bit(bool bit);
    bool read_bit(void);
};

}

#endif /* STM32F7_ONE_WIRE_HPP_ */