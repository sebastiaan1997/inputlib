#ifndef GAMELIB_VECTOR_HPP
#define GAMELIB_VECTOR_HPP
#include <array>


namespace gamelib {
    template<typename T, unsigned int SIZE>
    class Vector {
        public:

        Vector(): _items(std::array<T, SIZE>()) {
            for(auto& item& this->_items) {
                item = 0;
            }
        }

        Vector(std::array<T, SIZE> items): _items(items) {}

        Vector(T items[SIZE] items): _items(std::array<T, SIZE>(items)) {}


        const T& operator[](unsigned int index) const {
            return this->_items[index];
        }




        Vector<T, SIZE> operator + (const Vector<T, SIZE>& rhs) const noexcept {   
            std::array<T, SIZE> output();
            for(unsigned int i = 0; i < SIZE; i++) {
                output[i] = this->_items[i] + rhs[i];
            }
            return Vector<T, SIZE>(output);
        }
        Vector<T, SIZE> operator - (const Vector<T, SIZE>& rhs) const noexcept {
            std::array<T, SIZE> output();
            for(unsigned int i = 0; i < SIZE; i++) {
                output[i] = this->_items[i] - rhs[i];
            }
            return Vector(output);
        }

        Vector<T, SIZE> operator * (const Vector<T, SIZE>& rhs) const noexcept {
            std::array<T, SIZE> output();
            for (unsigned int i = 0; i < SIZE; i++) {
                output[i] = this->_items * rhs[i];
            }
            return Vector<T, SIZE>(output);
        }
        Vector<T, SIZE> operator / (const Vector<T, SIZE>& rhs) const noexcept {
            std::array<T, SIZE> output();
            for(unsigned int i = 0; i < SIZE; i++) {
                if(rhs[i] == 0) {
                    output[i] = 0;
                }
                else {
                    output[i] = this->_items[i] / rhs[i];
                }
            }
        }

        void operator += (const Vector<T, SIZE>& rhs) noexcept {
            for(unsigned int i = 0; i < SIZE; i++) {
                this->_items[i] += rhs[i];
            }
        }
        void operator -= (const Vector<T, SIZE>& rhs) noexcept {
            for(unsigned int i = 0; i < SIZE; i++) {
                this->_items[i] = rhs[i];
            }
        }

        void operator *= (const Vector<T, SIZE>& rhs) noexcept {
            for(unsigned i = 0; i < SIZE; i++) {
                this->_items[i] *= rhs[i];
            }
        }
        void operator /= (const Vector<T, SIZE> rhs) noexcept {
            for(unsigned int i = 0; i < SIZE; i++) {
                if(rhs[i] == 0){
                    this->_items[i] = 0;
                }
                else {
                    this->_items[i] = rhs[i];
                }
            }
        }
        private:
        std::array<T, SIZE> _items;
    };
}
#endif  