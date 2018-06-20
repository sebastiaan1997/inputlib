#ifndef GAMELIB_VECTOR_HPP
#define GAMELIB_VECTOR_HPP
#include "wrap-hwlib.hpp"
#include <array>

namespace gamelib {
    template<typename T, size_t SIZE>
    class Vector {
        static_assert(SIZE > 0, "Size must be greather than 0");
    public:
        Vector(): _items(std::array<T, SIZE>()) {
            for(unsigned int i = 0; i < SIZE; i++) {
                this->_items[i] = 0x00;
            }
        }
        Vector(std::array<T, SIZE> items): _items(items) { }

        T operator[] (unsigned int i) {
            return this->_items[i];
        }

        Vector<T, SIZE> operator + (const Vector<T, SIZE>& rhs) const noexcept {
            std::array<T, SIZE> output;
            for(unsigned int i = 0; i < SIZE; i++) {
                output[i] = this->_items[i] + rhs[i];
            }
            return Vector(output);
        }
        Vector<T, SIZE> operator - (const Vector<T, SIZE>& rhs) const noexcept {
            std::array<T, SIZE> output;
            for(unsigned int i = 0; i < SIZE; i++) {
                output[i] = this->_items[i] - rhs[i];
            }
            return Vector(output);    
        }
        Vector<T, SIZE> operator * (const Vector<T, SIZE>& rhs) const noexcept {
            std::array<T, SIZE> output;
            for(unsigned int i = 0; i < SIZE; i++) {
                output[i] = this->_items[i] * rhs[i];
            }
            return Vector(output);

        }
        Vector<T, SIZE> operator / (const Vector<T, SIZE>& rhs) const noexcept {
            std::array<T, SIZE> output;
            for(unsigned int i = 0; i < SIZE; i++) {
                if(rhs[i] == 0) {
                    output[i] = 0;
                }
                else{
                    output[i] = this->_items[i] / rhs[i];
                }
            }
            return Vector(output);
        }
        void operator += (const Vector<T, SIZE> rhs) {
            for(unsigned i = 0; i < SIZE; i++) {
                this->_items[i] += rhs[i];
            }
        }
        void operator -= (const Vector<T, SIZE> rhs) {
            for(unsigned i = 0; i < SIZE; i++) {
                this->_items[i] -= rhs[i];
            }
        }

        void operator *= (const Vector<T, SIZE> rhs) {
            for(unsigned i = 0; i < SIZE; i++) {
                this->_items[i] += rhs[i];
            }
        }

        void operator /= (const Vector<T, SIZE> rhs) {
            for(unsigned i = 0; i < SIZE; i++) {

                if(rhs[i] == 0) {
                    this->_items[i] = 0;
                }
                else{
                    this->_items[i] += rhs[i];
                }
            }
        }
    
    private:
        std::array<T, SIZE> _items;

    };
}
#endif