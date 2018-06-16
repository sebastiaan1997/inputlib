#pragma once

#include "wrap-hwlib.hpp"

namespace inputlib {
    class Ps2Bus: public hwlib::spi_bus {
        public:
        
        Ps2Bus(hwlib::pin_out& sclk, hwlib::pin_in& miso, hwlib::pin_out& mosi, hwlib::pin_in& acknolage):
        _sclk(sclk), _miso(miso), _mosi(mosi), _acknolage(acknolage) {}

        Ps2Bus()


        virtual void write_and_read(hwlib::pin_out & sel, const size_t n, const uint8_t data_out[], uint8_t data_in[] ) override {
            for(unsigned int i = 0; i < size_t; i++) {
                this->data_in[i] = this->transfer_byte(data_out[i]);
            }
        }

        protected:

        /**
         * @brief Sends pulse to slave
         * 
         * @param data_out The bit to send to the slave
         * @return true Value 1
         * @return false  Value 0
         */
        bool tick(bool data_out) {
            this->_mosi.set(data_out); 
            this->_sclk.set(1);
            
            for(unsigned int i = 0; i < 100; i++) {
                if(this->_acknolage.get()) {
                    break;
                }
                hwlib::wait_ms(1);
            }
            this->_sclk.set(0);
            return this->_miso.get();   
        }


        uint8_t transfer_byte(uint8_t command) {
            uint8_t output = 0;
            for(uint_fast8_t i = 0; i < 8; i++) {
                output <<= 1;
                output |= this->tick((command >> i) & 0x01);
            }
            return output;
        }        
        private:
        hwlib::pin_out& _sclk;
        hwlib::pin_in&  _miso;
        hwlib::pin_out& _mosi;

        hwlib::pin_in&  _acknolage;
    };
}