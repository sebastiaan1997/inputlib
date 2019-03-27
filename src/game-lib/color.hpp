//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef GAMELIB_COLOR_HPP
#define GAMELIB_COLOR_HPP

#include <cstdint>


namespace gamelib {
    /**
     * @brief Color object
     * 
     * @details
     * A wrapper around a uint_fast32_t
     * 
     */
class Color{
    public:
        /**
         * @brief Default constrctor, initializes with 0x00'00'00'00
         * 
         */
        Color(): _value(0x00'00'00'00) {}
        /**
         * @brief Copy Constructor
         * 
         * @param c 
         */
        Color(const Color& c): _value(c._value) {}
        /**
         * @brief Creates a new Color with the given int value
         * 
         * @param value 
         */
        Color(uint_fast32_t value): _value(value) {}
        /**
         * @brief Construct a new Color object
         * 
         * @param red 
         * @param green 
         * @param blue 
         * @param alpha 
         */
        Color(uint_fast8_t red, uint_fast8_t green, uint_fast8_t blue, uint_fast8_t alpha = 0x00):
            _value((red << 24) | (green << 16) | (blue << 8) | (alpha)) { }
        
        /**
         * @brief 
         * 
         * @return uint_fast8_t 
         */
        uint_fast8_t red() const noexcept;
        uint_fast8_t green() const noexcept;
        uint_fast8_t blue() const noexcept;
        uint_fast8_t alpha() const noexcept;

        /**
         * @brief 
         * 
         * @param redValue 
         * @return uint_fast8_t 
         */
        uint_fast8_t red(uint_fast8_t redValue) noexcept;
        uint_fast8_t green(uint_fast8_t greenValue) noexcept;
        uint_fast8_t blue(uint_fast8_t blueValue) noexcept;
        uint_fast8_t alpha(uint_fast8_t alphaValue) noexcept;


        uint_fast32_t value() const noexcept;
        uint_fast32_t& value_ref() noexcept;
        uint_fast32_t value(uint_fast32_t value) noexcept;


        Color operator + (Color rhs) const noexcept;
        Color operator - (Color rhs) const noexcept;

        Color operator << (unsigned int rhs) const noexcept;
        Color operator >> (unsigned int rhs) const noexcept;
        
        
        Color operator | (uint_fast32_t rhs) const noexcept;
        Color operator & (uint_fast32_t rhs) const noexcept;
        Color operator ^ (uint_fast32_t rhs) const noexcept;
        Color operator ~ () const noexcept;
        
        

        void operator += (Color rhs) noexcept;
        void operator -= (Color rhs) noexcept;
        void operator |= (uint_fast32_t rhs) noexcept;
        void operator &= (uint_fast32_t rhs) noexcept;
        void operator ^= (uint_fast32_t rhs) noexcept;


        uint_fast8_t operator[] (unsigned short int index) const noexcept;

    private:
        uint_fast32_t _value;
    };
}


#endif 