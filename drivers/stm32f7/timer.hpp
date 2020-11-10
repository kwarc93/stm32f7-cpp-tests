/*
 * timer.hpp
 *
 *  Created on: 9 lis 2020
 *      Author: kwarc
 */

#ifndef STM32F7_TIMER_HPP_
#define STM32F7_TIMER_HPP_

#include <cstdint>

namespace drivers
{

//-----------------------------------------------------------------------------

class timer
{
public:

    enum class id
    {
        timer1, timer2, timer3,
    };

    enum class channel
    {
        ch1, ch2, ch3, ch4
    };

    enum class channel_mode
    {
        ic, oc, pwm, one_pulse
    };

    timer(id id);
    virtual ~timer() {};

    bool set_frequency(uint32_t frequency);
    bool configure_channel(channel ch, channel_mode ch_mode);

protected:
    const uint8_t hw_id;
};

//-----------------------------------------------------------------------------

class counter : public timer
{
public:

    enum class mode
    {
        upcounting, downcounting, updowncounting
    };

    counter(id id, mode mode, uint32_t frequency, void (*irq_update_callback)(void));
    ~counter() {};

    uint32_t get_value(void);
private:
    void (*irq_update_callback)(void);
};

//-----------------------------------------------------------------------------

class pwm : public timer
{
public:
    pwm(id id, uint32_t frequency, float duty);
    ~pwm() {};

    void set_duty(channel channel, float duty);
    void enable(void);
    void disable(void);
};

//-----------------------------------------------------------------------------

}

#endif /* STM32F7_TIMER_HPP_ */
