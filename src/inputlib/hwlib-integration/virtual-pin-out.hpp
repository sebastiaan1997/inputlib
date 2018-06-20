#ifndef VIRTUAL_PIN_OUT_HPP
#define VIRTUAL_PIN_OUT_HPP
#include "../wrap-hwlib.hpp"
namespace inputlib {
    class VirtualPinOut: public hwlib::pin_out {
    public:
        VirtualPinOut(unsigned int i, hwlib::port_out& port): 
        _port(_port), _mask(i) {}

        virtual void set(bool value, hwlib::buffering buff = hwlib::buffering::unbuffered) {
            this->_port.set(value << this->_mask, buff);
        }

        virtual void flush() override {

        }

    private:
        hwlib::port_out& _port;
        unsigned int _mask;



    };
}

#endif