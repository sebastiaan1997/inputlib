#ifndef VIRTUAL_PIN_IN_HPP
#define VIRTUAL_PIN_IN_HPP


#include "../wrap-hwlib.hpp"
#include <cstdint> 

namespace inputlib {
    /**
     * @brief Virtual pin for use inside hwlib applications
     * 
     */
    class VirtualPinIn: public hwlib::pin_in {
        
    public:
        /**
         * @brief Construct a new Virtual Pin In object
         * 
         * @param i The location of the bit in the byte
         * @param port The source port for the pin
         */
        VirtualPinIn(unsigned int i , hwlib::port_in& port):
            _lastValue(false), _mask(0x01 << i), _port(port) {}

        virtual bool get(hwlib::buffering buff = hwlib::buffering::unbuffered) override {
            uint_fast8_t  portValue = this->_port.get();
            bool result = (portValue & this->_mask);
            return result;
        }

        virtual void refresh() override {
            this->_port.refresh();
        }
        
    private:
        bool _lastValue;
        unsigned int _mask;
        hwlib::port_in& _port;
    };
}
#endif