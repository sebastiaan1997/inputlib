#ifndef VIRTUAL_PIN_IN_HPP
#define VIRTUAL_PIN_IN_HPP


#include "../wrap-hwlib.hpp"
#include <cstdint> 
#include <type_traits>

namespace inputlib {
    /**
     * @brief Virtual pin that is linked to a value
     * 
     * @details
     * The virtual pin is created independently from the implementation of the target.
     * It means that you can link to any numeric value available.
     * Internally, if available it refreshes the port that the value is in. It shifts the bits 
     * into the right places by the position property and returns the value at the given position in the datatype.
     * 
     * @tparam BUFFER_T The type of the value that the virtual pin is using, must be a numeric value type
     */
    template<typename BUFFER_T>
    class VirtualPinIn: public hwlib::pin_in {
    static_assert(std::is_arithmetic<BUFFER_T>::value, "The BUFFER_T must be arithmetic");
    static_assert(!std::is_reference<BUFFER_T>::value, "The BUFFER_T must be a value type, not a reference");
    static_assert(!std::is_pointer<BUFFER_T>::value, "The BUFFER_T must be a value type, not a pointer");
    public:
       
        VirtualPinIn():
            _target(nullptr), _position(0), _port(nullptr) {};


        /**
         * @brief Create a new instance of a VirtualPinIn without targeting a port
         * 
         * @param Target The target value that is used to get the value
         * @param Position The position in the target value that is used to get the value
         */
        VirtualPinIn(BUFFER_T& target, unsigned int position):
            _target(&target), _position(position), _port(nullptr) {};

        VirtualPinIn(const VirtualPinIn<BUFFER_T>& copy): 
            _target(copy._target), _position(copy._position), _port(copy._port) 
            {};
        
        /**
         * @brief Create a new instance of a VirtualPinIn and target a port
         * 
         * @param target The target value that is used to get the value
         * @param position Position The position in the target value that is used to get the value
         * @param port A pointer to the target port
         */
        VirtualPinIn(BUFFER_T& target, unsigned int position, hwlib::port_in* port):
            _target(&target), _position(position), _port(port) {};

        /**
         * @brief Get the value of the virtual pin
         * 
         * @param buff Buffer type
         * @return true The value at the virtual pin is true
         * @return false The value at the virtual pin is false
         */
        virtual bool get(hwlib::buffering buff = hwlib::buffering::unbuffered) {
            if(this->_port != nullptr && buff == hwlib::buffering::unbuffered) {
                this->_port->refresh();
            }
            return ((*this->_target) >> this->_position) & 0x01;
        }
        /**
         * @brief Refresh the value at the virtual pin
         */
        virtual void refresh() override {
            if(this->_port == nullptr){
                return;
            }
            this->_port->refresh();
        }

    private:
        BUFFER_T* _target;
        unsigned int _position;
        hwlib::port_in* const _port;

    };
}
#endif