//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef PS2_TEST_BUS_HPP
#define PS2_TEST_BUS_HPP

#include <array>
#include "wrap-hwlib.hpp"
#include "ps2_bus.hpp"
#include "implementations/playstation/playstation-button-masks.hpp"


namespace inputlib {
    /**
     * @brief Ps2Testbus, emulating a Playstation2 Controlle. Useful for unittests
     * 
     *
     */
    class Ps2TestBus: public Ps2Bus {
    public:
        /**
         * @brief Construct a new Ps 2 Test Bus object, has no constructor parameters
         * 
         */
        Ps2TestBus(): 
            Ps2Bus(hwlib::pin_out_dummy, hwlib::pin_in_dummy, hwlib::pin_out_dummy, hwlib::pin_in_dummy),
            _configMode(false), _analog(false), _lock(false), _leftJoystickX(0) {}
        /**
         * @brief Handles SPI transactions 
         * 
         * @details
         * Handles SPI transactions as if it was a PS2 controller
         * 
         * @param sel Slave Select
         * @param n Number of bytes to process
         * @param data_out The command array, will be put at the MOSI Line
         * @param data_in The result array, got from the MISO line, will be filled during a transaction.
         */
        virtual void write_and_read(hwlib::pin_out & sel, const size_t n, const uint8_t data_out[], uint8_t data_in[] ) override {
            
            // Check if the padding byte is present
            if(data_out[0] != 0x01 && n <= 0) {
                return;
            }
            
            // Check if the second padding byte is present
            if(data_out[2] != 0x00 && n <= 2) {
                return;
            }
            // Adds start response byte
            data_in[0] = 0xFF;
            // Inserts the mode bit at the response
            this->insertModeResponse(n, data_out, data_in);
            data_in[2] = 0x5A;
            
            // Checks which procedure will be executed
            switch(data_out[1]) {
                case 0x41: // Buttons in poll response
                    break;
                case 0x42: // Poll command
                    // Add digital response bytes to the data_in array
                    this->insertDigitalButtonResponse(n, data_out, data_in);
                    // Add analog response bytes to the data_in array
                    this->insertAnalogButtonResponse(n, data_out, data_in);
                    break;
                case 0x43: // Enter or exit config mode
                     this->processConfigMode(n, data_out, data_in);
                    break;
                case 0x44: // Switch analog/digital mode
                    this->processSwitchModeCommand(n, data_out, data_in);
                    break;
                case 0x45: // Get more status info

                    break;
                case 0x46: // Unknown constants
                    
                    break;
                case 0x47: // Another unknown constant

                    break;

                case 0x4C: // Yet another unknown constants
                    break;

                case 0x4D: // Map bytes for the vibration motors 
                    
                    break;
                case 0x4F: // Add or remove states
                    this->processSetMaskCommand(n, data_out, data_in);
                    break;
                default:
                    for(unsigned int i = 3; i < n; i++) {
                        // If no valid command is provided, all other values will be set to 0x00
                        data_in[i] = 0x00;
                    }
                    return;
            }
        }
        bool configEnabled() const noexcept {
            return this->_configMode;
        }

        bool analogEnabled() const noexcept {
            return this->_analog;
        }

        bool modeLocked() const noexcept {
            return this->_lock;
        }
        std::array<bool, 19>& getValueMask() noexcept {
            return this->_mask;
        }

        void pressMode() noexcept {
            if(!this->_lock) {
                this->_analog = !this->_analog;
            }
        }



        void setButton(ButtonMask button, bool value) {
            this->_buttons = (0xFF'FF * value) & uint16_t(button);
        }
        void setButtons(uint16_t value) noexcept {
            this->_buttons = value;
        }

        void setLeftJoyStick(uint8_t x, uint8_t y) noexcept {
            this->_leftJoystickX = x;
            this->_leftJoystickY = y;
        }

        void setRightJoyStick(uint8_t x, uint8_t y) noexcept {
            this->_rightJoystickX = x;
            this->_rightJoystickY = y;
        }


    
    private:
        void insertModeResponse(const size_t n, const uint8_t data_out[], uint8_t data_in[]){
            uint8_t left = 0x00;
            // uint8_t right = 0x00;
            if(this->_configMode) {
                left = 0xF0;
            }
            else if(this->_analog) {
                left = 0x70;
            }
            else{
                left = 0x40;
            }
            data_in[1] = (left | 0x08);
        }

        /**
         * @brief Add the digital response buttons to the given response
         * 
         * @param data_out 
         * @param data_in 
         */
        void insertDigitalButtonResponse (const size_t n, const uint8_t data_out[], uint8_t data_in[]) {        
            data_in[3] = ((~this->_buttons & 0xFF'00) >>  8) * this->_mask[0];
            data_in[4] = (~this->_buttons & 0x00'FF)  * this->_mask[1];   
            // hwlib::cout << "Mask => " << this->_mask[0] << '|' << ((~this->_buttons) & 0xFF'00) << hwlib::endl;        
        }
        /**
         * @brief Add analog response to the data_in array
         * 
         * @param n 
         * @param data_out 
         * @param data_in 
         */
        void insertAnalogButtonResponse(const size_t n, const uint8_t data_out[], uint8_t data_in[]) {
            // if the analog mode is disabled, zeroes will be returned
            if(!this->_analog){
                for(unsigned int i = 5; i < n; i++) {
                    data_in[i] = 0x00;
                    return;
                }
            }
            data_in[5] = this->_mask[2] ? this->_rightJoystickX : 0;
            data_in[6] = this->_mask[3] ? this->_rightJoystickY : 0;

            data_in[7] = this->_mask[4] ? this->_leftJoystickX : 0; 
            data_in[8] = this->_mask[5] ? this->_leftJoystickY : 0;

            for(unsigned int i = 9; i < 16 + 9 && i < n; i++) {
                data_in[i] = (this->_buttons >> i & 0x01) * 0xFF * this->_mask[6 + i];
            }
        }

        /**
         * @brief Processes the enter of exit config command of the playstation controller
         * 
         * @param n The size of the command string 
         * @param data_out The command string
         * @param data_in The output back to the program 
         */
        void processConfigMode(const size_t n, const uint8_t data_out[], uint8_t data_in[]) {
            if(data_out[3] == 0x01) {
                this->_configMode = true;
            }
            else if(data_out[3] == 0x00) {
                this->_configMode = false;
            }
        }
        /**
         * @brief Process the switch analog-digital command to the playstation controller
         * 
         * @param n The size of the array
         * @param data_out The command string
         * @param data_in The output data to the program
         */
        void processSwitchModeCommand(const size_t n, const uint8_t data_out[], uint8_t data_in[]) {
            for(unsigned int i = 3; i < n; i++){
                data_in[i] = 0x00;
            }
            if(!this->_configMode) {
                return;
            }
            this->_analog = data_out[3] == 0x01;
            this->_lock = data_out[4] == 0x03;
        }

        void processSetMaskCommand(const size_t n, const uint8_t data_out[], uint8_t data_in[]) {
            if(!this->_configMode) {
                return;
            }
            uint32_t maskInput = 0x00;
            maskInput |= data_out[3] << 16;
            maskInput |= data_out[4] << 8;
            maskInput |= data_out[5];
            for(unsigned int i = 0; i < 19 && i < n; i++) {
                
                this->_mask[18 - i] = maskInput  & 0x01;
                maskInput >>= 1;
            }
        }


        bool _configMode;
        bool _analog;
        bool _lock;
        uint16_t _buttons = 0x00;
        std::array<bool, 19>  _mask = {1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0};

        uint8_t _rightJoystickX = 0x00;
        uint8_t _rightJoystickY = 0x00;

        uint8_t _leftJoystickX = 0x00;
        uint8_t _leftJoystickY = 0x00;

    
    };
}
#endif