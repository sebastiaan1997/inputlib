#ifndef GAMELIB_VECTOR_HPP
#define GAMELIB_VECTOR_HPP
#include <array>
#include "../wrap-hwlib.hpp"

namespace gamelib {
    /**
     * @brief Vector that can be used for mathematical operations
     * 
     * @tparam T The inner type of the vector
     * @tparam SIZE The size of the vector
     */
    template<typename T, unsigned int SIZE>
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

            static_assert(std::is_arithmetic<T>::value, "The right hand side of a + operation of a vector must be arithmetic");
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
        
        template<typename RHS_T>
        void operator += (const Vector<RHS_T, SIZE>& rhs) noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a += operation of a vector must be arithmetic");
            for(unsigned int i = 0; i < SIZE; i++) {
                this->_items[i] += rhs[i];
            }
        }
        template<typename RHS_T>
        void operator -= (const Vector<RHS_T, SIZE>& rhs) noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a -= operation of a vector must be arithmetic");
            for(unsigned int i = 0; i < SIZE; i++) {
                this->_items[i] = rhs[i];
            }
        }

        template<typename RHS_T>
        void operator *= (const Vector<RHS_T, SIZE>& rhs) noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a *= operation of a vector must be arithmetic");
            for(unsigned i = 0; i < SIZE; i++) {
                this->_items[i] *= rhs[i];
            }
        }
        
        template<typename RHS_T>
        void operator /= (const Vector<RHS_T, SIZE> rhs) noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a /= operation of a vector must be arithmetic");
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
        /**
         * @brief Print vector to ostream provided by hwlib
         * 
         * @param lhs The ostream to print to
         * @param rhs The Vector to print
         * @return hwlib::ostream&
         */
        friend hwlib::ostream& operator << (hwlib::ostream& lhs, const Vector<T, SIZE>& rhs) {
            lhs<< '{';
            for(unsigned int i = 0; i < rhs._items.size(); i++) {
                if (sizeof(decltype(rhs[0])) == 1 && !std::is_same<T, char>::value){
                    lhs << int(rhs._items[i]);
                }
                else{
                    lhs << rhs._items[i];
                }


                if(i < (rhs._items.size() - 1)) {
                    lhs << ',';
                }

            }
            lhs << '}';

            return lhs;

        }

        typedef T type;
        protected:
        std::array<T, SIZE> _items;


    };

    template<size_t SIZE>
    using Coordinate = Vector<unsigned int, SIZE>;
    

}
#endif  