/*
 * hal_led.cpp
 *
 *  Created on: 25 paź 2020
 *      Author: kwarc
 */

#include "hal_led.hpp"

#include <cmath>

using namespace hal;

// Gamma brightness lookup table <https://victornpb.github.io/gamma-table-generator>
// gamma = 2.00 steps = 256 range = 0-255
static const uint8_t gamma_lut[256] =
{
     0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   1,   1,   1,   1,
     1,   1,   1,   1,   2,   2,   2,   2,   2,   2,   3,   3,   3,   3,   4,   4,
     4,   4,   5,   5,   5,   5,   6,   6,   6,   7,   7,   7,   8,   8,   8,   9,
     9,   9,  10,  10,  11,  11,  11,  12,  12,  13,  13,  14,  14,  15,  15,  16,
    16,  17,  17,  18,  18,  19,  19,  20,  20,  21,  21,  22,  23,  23,  24,  24,
    25,  26,  26,  27,  28,  28,  29,  30,  30,  31,  32,  32,  33,  34,  35,  35,
    36,  37,  38,  38,  39,  40,  41,  42,  42,  43,  44,  45,  46,  47,  47,  48,
    49,  50,  51,  52,  53,  54,  55,  56,  56,  57,  58,  59,  60,  61,  62,  63,
    64,  65,  66,  67,  68,  69,  70,  71,  73,  74,  75,  76,  77,  78,  79,  80,
    81,  82,  84,  85,  86,  87,  88,  89,  91,  92,  93,  94,  95,  97,  98,  99,
   100, 102, 103, 104, 105, 107, 108, 109, 111, 112, 113, 115, 116, 117, 119, 120,
   121, 123, 124, 126, 127, 128, 130, 131, 133, 134, 136, 137, 139, 140, 142, 143,
   145, 146, 148, 149, 151, 152, 154, 155, 157, 158, 160, 162, 163, 165, 166, 168,
   170, 171, 173, 175, 176, 178, 180, 181, 183, 185, 186, 188, 190, 192, 193, 195,
   197, 199, 200, 202, 204, 206, 207, 209, 211, 213, 215, 217, 218, 220, 222, 224,
   226, 228, 230, 232, 233, 235, 237, 239, 241, 243, 245, 247, 249, 251, 253, 255,
};

led::led(hal::interface::led *interface)
{
    this->interface = interface;
    this->brightness = 0;
}

led::~led(void)
{
    delete this->interface;
}

void led::set(uint8_t brightness)
{
    this->brightness = gamma_lut[brightness];
    this->interface->set(this->brightness);
}

void led::set(bool state)
{
    uint8_t brightness = state ? 255 : 0;
    this->set(brightness);
}

//---------------------------------------------------------------------------

rgb_led::rgb_led(const std::array<hal::interface::led *, 3> &interface)
{
    this->r = new led(interface[0]);
    this->g = new led(interface[1]);
    this->b = new led(interface[2]);
}

void rgb_led::set(uint8_t r, uint8_t g, uint8_t b)
{
    this->r->set(r);
    this->g->set(g);
    this->b->set(b);
}

void rgb_led::set(bool r, bool g, bool b)
{
    this->r->set(r);
    this->g->set(g);
    this->b->set(b);
}

void rgb_led::set(float h, float s, float v)
{
    if (h > 360.0f || h < 0.0f || s > 1.0f || s < 0.0f || v > 1.0f || v < 0.0f)
        return;

    float c = s * v;
    float x = c * (1 - std::fabs(std::fmod(h / 60.0, 2.0f) - 1));
    float m = v - c;
    float r, g, b;

    if (h >= 0 && h < 60)
        r = c, g = x, b = 0;
    else if (h >= 60 && h < 120)
        r = x, g = c, b = 0;
    else if (h >= 120 && h < 180)
        r = 0, g = c, b = x;
    else if (h >= 180 && h < 240)
        r = 0, g = x, b = c;
    else if (h >= 240 && h < 300)
        r = x, g = 0, b = c;
    else
        r = c, g = 0, b = x;

    uint8_t R = (r + m) * UINT8_MAX;
    uint8_t G = (g + m) * UINT8_MAX;
    uint8_t B = (b + m) * UINT8_MAX;

    this->set(R, G, B);
}

