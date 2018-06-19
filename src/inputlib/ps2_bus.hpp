#pragma once

#include "wrap-hwlib.hpp"

namespace inputlib {
    class Ps2Bus: public hwlib::spi_bus {
        public:
        Ps2Bus() = delete;
        Ps2Bus(Ps2Bus& ps2) = delete;

        Ps2Bus(hwlib::pin_out& sclk, hwlib::pin_in& miso, hwlib::pin_out& mosi, hwlib::pin_in& acknolage, unsigned int transferRate = 0):
        _sclk(sclk), _miso(miso), _mosi(mosi), _acknolage(acknolage), _transferRate(transferRate) {}

        /**
         * @brief 
         * 
         * @param sel 
         * @param n 
         * @param data_out 
         * @param data_in 
         */
        virtual void write_and_read(hwlib::pin_out & sel, const size_t n, const uint8_t data_out[], uint8_t data_in[] ) override {
            sel.set(false);
            sel.flush();
            for(unsigned int i = 0; i < n; i++) {
                data_in[i] = this->transfer_byte(data_out[i]);
            }
            sel.set(true);
            sel.flush();
        }

        protected:

        /**
         * @brief Executes a tick. Transfers one bit in each direction
         * 
         * @param data_out The bit to send to the slave
         * @return true Value 1
         * @return false  Value 0
         */
        bool tick(bool data_out) {
            this->_mosi.set(data_out); 
            this->_mosi.flush();
            hwlib::wait_us(10);
            this->_sclk.set(1);
            this->_sclk.flush();
            hwlib::wait_us(10);
            bool inputValue = this->_miso.get();
            this->_sclk.set(0);
            this->_sclk.flush();
            return inputValue;
        }
        /**
         * @brief Transfers one byte in each direction with the slave device
         * 
         * @param command 
         * @return uint8_t 
         */
        uint8_t transfer_byte(uint8_t command) {
            
            uint8_t output = 0;
            for(uint_fast8_t i = 0; i < 8; i++) {
                output <<= 1;
                // bool data = ((command >> i) & 1);
               
                output |= this->tick((command >> i) & 1);
            }
            return output;
        }
        private:
        hwlib::pin_out& _sclk;
        hwlib::pin_in&  _miso;
        hwlib::pin_out& _mosi;
        hwlib::pin_in&  _acknolage;
        unsigned int _transferRate;
    };
}