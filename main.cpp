/*
 * main.cpp
 *
 *  Created on: 18 paź 2020
 *      Author: kwarc
 */

#include <stm32f7xx.h>

#include <iostream>
#include <cstring>

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
    if (globvar == 0)
        globvar++;

    std::cout << "In main" << std::endl;

    auto c = new test_class();
    c->var++;
    c->fvar *= 2;
    delete c;

    char a[14];
    memset(a, 0, sizeof(a));

    while(true);
    return 0;
}

