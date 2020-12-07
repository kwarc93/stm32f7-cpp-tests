/*
 * ds18b20.cpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#include "ds18b20.hpp"

#include <drivers/stm32f7/delay.hpp>

using namespace drivers;

ds18b20::ds18b20(drivers::gpio::io io) : one_wire {io}
{

}

float ds18b20::read_temperature(void)
{
    float celsius {0};
    bool sensor_present = this->one_wire.reset_pulse();

    if (sensor_present)
    {
        std::byte cmd1[2] {std::byte{0xCC}, std::byte{0x44}};
        this->one_wire.write(cmd1, sizeof(cmd1));

        delay::ms(1000);

        this->one_wire.reset_pulse();

        std::byte cmd2[2] {std::byte{0xCC}, std::byte{0xBE}};
        this->one_wire.write(cmd2, sizeof(cmd2));

        std::byte temp_reg[2];
        this->one_wire.read(temp_reg, sizeof(temp_reg));

        this->one_wire.reset_pulse();

        int16_t *temp = reinterpret_cast<int16_t*>(temp_reg);
        celsius = -*temp / 16.0f;
    }

    return celsius;
}

