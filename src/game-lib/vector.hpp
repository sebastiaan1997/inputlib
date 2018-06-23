#ifndef GAMELIB_VECTOR_HPP
#define GAMELIB_VECTOR_HPP
#include <array>

namespace gamelib {
    template<typename T, unsigned int SIZE, bool = false>
    class Vector {
        public:
        Vector(): _items(std::array<T, SIZE>()) {
            for(auto& item: this->_items) {
                item = 0;
            }
        }

        Vector(std::initializer_list<T> items): _items(std::array<T, SIZE>()) {
            unsigned int i = 0;
            for(auto& item: items) {
                this->_items[i] = item;
                i++;
            }
        }

        Vector(std::array<T, SIZE> items): _items(items) {}

        Vector(T items[SIZE]): _items(std::array<T, SIZE>(items)) {}


        const T& operator[](unsigned int index) const {
            return this->_items[index];
        }

        template<typename RHS_T>
        Vector<T, SIZE> operator + (const Vector<RHS_T, SIZE>& rhs) const noexcept {   

            static_assert(std::is_arithmetic<T>::value, "The right hand side of the + operation of a vector must be arithmetic");
            std::array<T, SIZE> output;
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
        /**
         * @brief 
         * 
         * @param rhs 
         */
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
        bool isZero() const noexcept{
            for(auto& item: this->_items) {
                if(item != 0){
                    return false;
                }
            }
            return true;
        }

        bool any(T target) const noexcept {
            for(auto& item: this->_items) {
                if(item == target) {
                    return true;
                }
            }
            return false;
        }

        bool all(T target) const noexcept {
            for(auto& item: this->_items) {
                if(item != target) {
                    return false;
                }
            }
            return false;
        }

        T get(unsigned int index) {
            return this->_items[index];
        }

        
        protected:
        std::array<T, SIZE> _items;
    };

    template<size_t SIZE>
    using Coordinate = Vector<unsigned int, SIZE>;
    

}
#endif  