//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#include "color.hpp"

namespace gamelib { 
    uint_fast8_t Color::red() const noexcept {
        return (this->_value >> 24) & 0xFF;
    }

    uint_fast8_t Color::green() const noexcept {
        return (this->_value >> 16) & 0xFF;
    }

    uint_fast8_t Color::blue() const noexcept {
        return (this->_value >> 8) & 0xFF;
    }

    uint_fast8_t Color::alpha() const noexcept {
        return this->_value & 0xFF;
    }

    uint_fast8_t Color::red(uint_fast8_t redValue) noexcept {
        this->_value &= 0xFF'FF'FF;
        this->_value |= (redValue << 24);
        return redValue;
    }

    uint_fast8_t Color::green(uint_fast8_t greenValue) noexcept {
        this->_value &= 0xFF'00'FF'FF;
        this->_value |= (greenValue << 16);
        return greenValue;
    }
    uint_fast8_t Color::blue(uint_fast8_t blueValue) noexcept {
        this->_value &= 0xFF'FF'00'FF;
        this->_value |= (blueValue << 8);
        return blueValue;
    }

    uint_fast8_t Color::alpha(uint_fast8_t alphaValue) noexcept  {
        this->_value &= ~0xFF;
        this->_value |= (alphaValue & 0xFF);
    }

    Color Color::operator + (Color rhs) const noexcept {
        return Color(this->_value + rhs._value);
    }

    Color Color::operator - (Color rhs) const noexcept {
        return Color(this->_value - rhs._value);
    }

    Color Color::operator << (unsigned int rhs) const noexcept {
        return Color(this->_value << rhs);
    }
    Color Color::operator >> (unsigned int  rhs) const noexcept {
        return Color(this->_value >> rhs);
    }

    Color Color::operator | (uint_fast32_t rhs) const noexcept {
        return Color(this->_value | rhs);
    }      

    void Color::operator += (Color rhs) noexcept {
        this->_value += rhs._value;
    }

    void Color::operator -= (Color rhs) noexcept {
        this->_value -= rhs._value;
    }

    uint_fast8_t Color::operator[] (unsigned short int index) const noexcept {
        return this->_value >> (24 - (8 * index)) & 0xFF;
    }

}