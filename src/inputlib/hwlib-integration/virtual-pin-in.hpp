#ifndef VIRTUAL_PIN_IN_HPP
#define VIRTUAL_PIN_IN_HPP


#include "../wrap-hwlib.hpp"
#include <cstdint> 

namespace inputlib {
    class VirtualPinIn: public hwlib::pin_in {
        
    public:
        VirtualPinIn(unsigned int i , hwlib::port_in& port):
            _lastValue(false), _mask(1 << i), _port(port) {}

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