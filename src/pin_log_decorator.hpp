#pragma once
#include "wrap-hwlib.hpp"
#include <array>

class pin_out_log: public hwlib::pin_out {
public:
    pin_out_log(unsigned int pin_number, hwlib::pin_out& pin_out, bool logEnabled = true): _slave(pin_out), _pinNumber(pin_number), _logEnabled(logEnabled) {
        hwlib::cout << "Attatched logger to pin_out " << pin_number << hwlib::endl << hwlib::flush;
    }
    
    virtual void set(bool value, hwlib::buffering buff = hwlib::buffering::unbuffered) override {
        if(this->_logEnabled) {
            hwlib::cout << "Pin out " << this->_pinNumber << " => " << value <<hwlib::endl << hwlib::flush;
        }
        this->_slave.set(value, buff);
    }
    void enable_log(bool value) {
        this->_logEnabled = value;
    }

private:
    hwlib::pin_out& _slave;
    const unsigned int _pinNumber;
    bool _logEnabled;
};

class pin_in_log: public hwlib::pin_in {
public:
    pin_in_log(unsigned int pin_number, hwlib::pin_in& pin_in, bool _logEnabled = true): 
        _slave(pin_in), _pinNumber(pin_number), _logEnabled(_logEnabled) {
            hwlib::cout << "Attatched logger to pin_in " << pin_number << hwlib::endl << hwlib::flush;
        }

    virtual bool get(hwlib::buffering buff = hwlib::buffering::unbuffered) override {
        bool value = this->_slave.get(buff);
        if(this->_logEnabled) {
             hwlib::cout << "Pin in " << this->_pinNumber << " => " << value <<hwlib::endl << hwlib::flush;
        }
        return value;
    }

    void enable_log(bool value) {
        this->_logEnabled = value;
    }

    private:
    hwlib::pin_in& _slave;
    const unsigned int _pinNumber;
    bool _logEnabled;
};

