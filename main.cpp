/*
 * main.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: kwarc
 */

#include <iostream>
#include <cstring>

#include <hal/hal.hpp>
#include <drivers/stm32f7/gpio.hpp>

class test_class
{
public:
    test_class()
    {
        var = 10;
        fvar = 3.14f;
        std::cout << "In constructor" << std::endl;
    }

    ~test_class()
    {
        std::cout << "In destructor" << std::endl;
    }

    int var;
    float fvar;
};

int globvar;

int main(void)
{
    hal::system_init();

    if (globvar == 0)
        globvar++;

    std::cout << "In main" << std::endl;

    auto c = new test_class();
    c->var++;
    c->fvar *= 2;
    delete c;

    char a[14];
    memset(a, 0, sizeof(a));

    std::cout << "Enabling green LED..." << std::endl;
    gpio::init(gpio::port::I, 1);
    gpio::write(gpio::port::I, 1, true);
    gpio::write(gpio::port::I, 1, false);

    std::cout << "Entering infinite loop..." << std::endl;
    while(true);
    return 0;
}

