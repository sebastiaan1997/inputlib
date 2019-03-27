//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


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
        static_assert(std::is_arithmetic<T>::value || SIZE > 0, 
            "The inner type of a Vector must be arithemitc  and the SIZE must be greather than 0");
        static_assert(std::is_arithmetic<T>::value, "The inner type of a Vector must be arithemitc");
        static_assert(SIZE > 0, "The size of a vector must be greather than 0");
        public:
        /**
         * @brief Construct a new Vector object, all values are 0 by default
         *  
         * 
         * 
         */
        Vector(): _items(std::array<T, SIZE>()) {
            for(auto& item: this->_items) {
                item = 0;
            }
        }
        /**
         * @brief Construct a new Vector object
         * 
         * @param defaultValue 
         */
        Vector(T defaultValue): _items(std::array<T, SIZE>()) {
            for(auto& item: this->_items) {
                item = defaultValue;
            }
        }
        /**
         * @brief Construct a new Vector object
         * 
         * @param items 
         */
        Vector(std::initializer_list<T> items): _items(std::array<T, SIZE>()) {
            unsigned int i = 0;
            for(auto& item: items) {
                this->_items[i] = item;
                i++;
            }
        }
        /**
         * @brief Construct a new Vector object
         * 
         * @param items 
         */
        Vector(std::array<T, SIZE> items): _items(items) {}
        /**
         * @brief Construct a new Vector object
         * 
         * @param items 
         */
        Vector(T items[SIZE]): _items(std::array<T, SIZE>(items)) {}
        /**
         * @brief 
         * 
         * @param index 
         * @return const T& 
         */
        const T& operator[](unsigned int index) const {
            return this->_items[index];
        }
        /**
         * @brief 
         * 
         * @tparam RHS_T 
         * @param rhs 
         * @return Vector<T, SIZE> 
         */
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
        Vector<T, SIZE> operator * (const RHS_T rhs) {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a * operation of a vector must be arithmetic");
            std::array<T, SIZE> output;
            for(unsigned int i = 0; i < SIZE; i++) {
                output[i] = this->_items[i] * rhs;
            }
            return Vector<T, SIZE>(output);
        }


        template<typename RHS_T>
        Vector<T, SIZE> operator / (const RHS_T rhs) {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a / operation of a vector must be arithmetic");
            std::array<T, SIZE> output;
            for(unsigned int i = 0; i < SIZE; i++) {
                output[i] = this->_items[i] / rhs;
            }
            return Vector<T, SIZE>(output);
        }

        /**
         * @brief 
         * 
         * @tparam RHS_T 
         * @param rhs 
         */
        template<typename RHS_T>
        void operator += (const Vector<RHS_T, SIZE>& rhs) noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a += operation of a vector must be arithmetic");
            for(unsigned int i = 0; i < SIZE; i++) {
                this->_items[i] += rhs[i];
            }
        }
        /**
         * @brief 
         * 
         * @tparam RHS_T 
         * @param rhs 
         */
        template<typename RHS_T>
        void operator -= (const Vector<RHS_T, SIZE>& rhs) noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a -= operation of a vector must be arithmetic");
            for(unsigned int i = 0; i < SIZE; i++) {
                this->_items[i] = rhs[i];
            }
        }
        /**
         * @brief 
         * 
         * @tparam RHS_T 
         * @param rhs 
         */
        template<typename RHS_T>
        void operator *= (const Vector<RHS_T, SIZE>& rhs) noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a *= operation of a vector must be arithmetic");
            for(unsigned i = 0; i < SIZE; i++) {
                this->_items[i] *= rhs[i];
            }
        }
        /**
         * @brief 
         * 
         * @tparam RHS_T 
         * @param rhs 
         */
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

        /**
         * @brief Compares 2 vectors, the numbers at the same indexes are compared
         * 
         * @tparam RHS_T The type of the right hand side
         * @param rhs The right hand side
         * @return true All the values at the same position of the vector at the right are greather than their equivalent at the left side
         * @return false Not all / no values at the same position in the vector at the right side are greather than at the left side
         */
        template<typename RHS_T>
        bool operator > (const Vector<RHS_T, SIZE> rhs) const noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a > operation of a vector must be arithmetic");
            for(unsigned int i = 0 ; i < SIZE; i++) {
                if(this->_items[i] <= rhs._items[i]){
                    return false;
                }
            }
            return true;
        }

        template<typename RHS_T>
        bool operator < (const Vector<RHS_T, SIZE> rhs) const noexcept {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a < operation of a vector must be arithmetic");
            for(unsigned int i = 0; i < SIZE; i++) {
                if(this->_items[i] >= rhs._items[i]) {
                    return false;
                }
            }
            return true;
        }

        template<typename RHS_T>
        bool operator >= (RHS_T rhs) {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a > operation of a vector must be arithmetic");
            for(unsigned int i = 0 ; i < SIZE; i++) {
                if(this->_items[i] < rhs._items[i]){
                    return false;
                }
            }
            return true;
        }

        template <typename RHS_T>
        bool operator <= (RHS_T rhs) {
            static_assert(std::is_arithmetic<RHS_T>::value, "The right hand side of a < operation of a vector must be arithmetic");
            for(unsigned int i = 0; i < SIZE; i++) {
                if(this->_items[i] > rhs._items[i]) {
                    return false;
                }
            }
            return true;
            
        }
        /**
         * @brief Checks if all values in the vector are 0
         * 
         * @return true All values in the vector are 0
         * @return false Not all/ none of the values in the vector are 0
         */
        bool isZero() const noexcept{
            for(auto& item: this->_items) {
                if(item != 0){
                    return false;
                }
            }
            return true;
        }
        
        /**
         * @brief Checks if all values in the vetor are positive (> 0)
         * 
         * @return true All values inside the vector are greather than 0 (positive)
         * @return false Not all, none of the values inside the vector are greather than 0 (positive)
         */
        bool isPositive() const noexcept {
            for(auto& item: this->_items) {
                if(item <= 0) {
                    return false;
                }
            }
            return true;
        }

        /**
         * @brief Checks if all values in the vetor are negative (< 0)
         * 
         * @return true All values inside the vector are smaller than 0 (negative)
         * @return false Not all, none of the values inside the vector are greather than 0 (negative)
         */
        bool isNegative() const noexcept  {
            for(auto& item: this->_items) {
                if(item >= 0) {
                    return false;
                }
            }
            return true;
        }
        /**
         * @brief Checks if all values of the vector are in the given range
         * 
         * @tparam START_T The type of the start value
         * @tparam END_T The type of the end value
         * @param start The value of the start of the range to check
         * @param end The value of the end of the range to check
         * @return true All the values in the vector are in the given range
         * @return false Not all values are in the range of the vector
         */
        template<typename START_T, typename END_T>
        bool valuesInRange(START_T start, END_T end) {
            for(auto& item: this->_items) {
                if(item < start || item > end) {
                    return false;
                }
            }
            return true;
        }

        /**
         * @brief Checks if any value inside the vector equals the target
         * 
         * @param target The target to search for
         * @return true The given target is present in the vector
         * @return false The given target is not present in the vector
         */
        bool any(const T& target) const noexcept {
            for(auto& item: this->_items) {
                if(item == target) {
                    return true;
                }
            }
            return false;
        }
        /**
         * @brief Checks if all values inside the vector are equal to the target
         * 
         * @tparam TARGET_T The type of the target
         * @param target 
         * @return true 
         * @return false 
         */
        template<typename TARGET_T>
        bool all(TARGET_T target) const noexcept {
            static_assert(std::is_arithmetic<TARGET_T>::value, "The target type of the Vector::all() function must be arithmetic");
            for(auto& item: this->_items) {
                if(item != target) {
                    return false;
                }
            }
            return false;
        }
        /**
         * @brief Get a value at the given index
         * 
         * @param index The index of the value to get
         * @return T 
         */
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