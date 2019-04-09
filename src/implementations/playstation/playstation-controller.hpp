//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef INPUTLIB_PLAYSTATION2_PLAYSTATION__CONTROLLER_HPP
#define INPUTLIB_PLAYSTATION2_PLAYSTATION__CONTROLLER_HPP
#include "../../wrap-hwlib.hpp"
#include "../../ps2_bus.hpp"
#include "../../hwlib-integration/virtual-pin-in.hpp"
#include "../../hwlib-integration/hwlib-common-device-interface.hpp"
#include "playstation-byte-mapping.hpp"
#include <array>


namespace inputlib {
    /**
     * @brief An implementation of a playstation controller
     * 
     */
    class PlaystationController: public hwlib::port_in/*, IHwlibCommonDeviceInterface*/ {
        typedef VirtualPinIn<uint_fast16_t> vpin;
    public:
        /**
         * @brief Construct a new Playstation Controller object
         * 
         * @param bus The bus to use to communicate with the controller
         * @param select The slave select line
         */
        PlaystationController(Ps2Bus& bus, hwlib::pin_out& select): 
            _bus(bus), _select(select), _buffer(0x00), _defaultBuffer({0}),
                _analog(false), _config(false), _locked(false)   {}
        
        /**
         * @brief Initializes the playstation controller
         * @Details
         * The controller wil be fully enabled, locked to analog
         * 
         */
        void init() {
            std::array<uint8_t, 21> output = { 0 };
            this->setConfigMode(true);
            hwlib::wait_ms(1);
            this->setAnalogEnabled(true, true);
            hwlib::wait_ms(1);
            {
                auto enableButtons = this->_enableAllButtonsCommand;
                this->_bus.write_and_read(this->_select, 9, enableButtons.data(), output.data());
            }
            hwlib::wait_ms(1);
            this->setConfigMode(false);

        }
        /**
         * @brief Get a 2 byte representation of the digital buttons at the PS 2 controller
         * 
         * @return uint16_t 
         */
        uint16_t getButtonBytes(){
            auto output = this->executeCommand(this->_readGamepadCommand);
            
            // hwlib::cout << hwlib::endl << hwlib::flush;
            uint16_t value = (uint16_t(output[3]) << 8 | output[4]);
            // hwlib::cout << value << hwlib::endl << hwlib::flush;
            // hwlib::cout << "X => " << int((output[3] >> 1) & 0x01) << hwlib::endl << hwlib::flush;
            return value;
        }

        /**
         * @brief Get the Joysticks object
         * 
         * @return hwlib::location 
         */
        hwlib::location getRightJoystick() {
            if(!this->_analog) {
                this->setAnalogEnabled(true, true);
            }
            const std::array<uint8_t, 21>& output = this->executeCommand(this->_pollCommand);
            
            // Keep out, it's easy
            const PullAllResponse& values = *reinterpret_cast<const PullAllResponse*>(&output);

            this->_buffer = values.digitalButtons1 << 8 | values.digitalButtons2;
            hwlib::location l({ values.rightJoystickX, values.rightJoystickY });
            return l;
        }

        hwlib::location getLeftJoystick() {
            if(!this->_analog) {
                this->setAnalogEnabled(true, true);
            }
            const std::array<uint8_t, 21>& output = this->executeCommand(this->_pollCommand);
            const PullAllResponse& values = *reinterpret_cast<const PullAllResponse*>(&output);
            return { values.leftJoystickX, values.leftJoystickY };
        }

        /**
         * @brief Reports that this port has 8 buttons
         * 
         * @return uint_fast8_t 8
         */
        virtual uint_fast8_t number_of_pins() override {
            return 8;
        }

        /**
         * @brief 
         * 
         * @param buf 
         * @return uint_fast8_t 
         */
        virtual uint_fast8_t get(hwlib::buffering buf = hwlib::buffering::unbuffered) override {
            if(buf == hwlib::buffering::unbuffered) {
                this->refresh();
            }
            return this->_hwlibBuffer;
             // TODO Invent a useful mapping
        }

        /**
         * @brief Refreshes the HWLib buffer for the controller
         */
        virtual void refresh() override {
            uint_fast16_t values = this->getButtonBytes();
            this->_buffer = ~values;
            uint_fast8_t output = 0x00;
            output |= ((output & 0x0F << 9) >> 5);
            output |= 0x0F & output;
            this->_hwlibBuffer = ~output;
        }

        vpin pinButtonSelect() {
            return vpin(this->_buffer, 15, this);
        }

        vpin pinButtonL3() {
            return vpin(this->_buffer, 14, this);
        }
        vpin pinButtonR3() {
            return vpin(this->_buffer, 13, this);
        }
        vpin pinButtonStart() {
            return vpin(this->_buffer, 12, this);
        }
        vpin pinButtonUp() {
            return vpin(this->_buffer, 11, this);
        }

        vpin pinButtonRight() {
            return vpin(this->_buffer, 10, this);
        }
        vpin pinButtonDown() {
            return vpin(this->_buffer, 9, this);
        }

        vpin pinButtonLeft() {
            return vpin(this->_buffer, 8, this);
        }

        vpin pinButtonL2() {
            return vpin(this->_buffer, 7, this);
        }

        vpin pinButtonR2() {
            return vpin(this->_buffer, 6, this);
        }

        vpin pinButtonL1() {
            return vpin(this->_buffer, 5, this);
        }

        vpin pinButtonR1() {
            return vpin(this->_buffer, 4, this);
        }

        vpin pinButtonTriangle() {
            return vpin(this->_buffer, 3, this);
        }

        vpin pinButtonCircle() {
            return vpin(this->_buffer, 2, this);
        }

        vpin pinButtonX() {
            return vpin(this->_buffer, 1, this);
        }
        vpin pinButtonSquare() {
            return vpin(this->_buffer, 0, this);
        }
    protected:
        /**
         * @brief Returns if the controller is in config mode
         * 
         * @return true The controller is in config mode
         * @return false The controller is not in config mode
         */
        bool isInConfigMode() const noexcept {
            return this->_config;
        }
        /**
         * @brief Enabled or disabled the config mode of the controller
         * 
         * @param enabled If true, the config-mode will be enabled, if false the config mode will be disabled
         */
        void setConfigMode(bool enabled) {
            if(enabled && !this->_config){
                this->executeCommand(this->_enterConfigCommand);
            }
            else if(!enabled && this->_config) {
                this->executeCommand(this->_exitConfigCommand);
            }
            this->_config = enabled;
        }
        /**
         * @brief Returns if analog mode is enabled
         * 
         * @return true 
         * @return false 
         */
        bool analogEnabled(hwlib::buffering buff = hwlib::buffering::buffered) const noexcept {
            return this->_analog;
        }

        void setAnalogEnabled(bool enabled, bool locked = false) noexcept {
            this->setConfigMode(true);
            
            this->_setModeCommand[3] = enabled ? uint8_t(0x01) : uint8_t(0x00);
            this->_setModeCommand[4] = locked ? uint8_t(0x03) : uint8_t(0x00);
            this->executeCommand(this->_setModeCommand);
            this->setConfigMode(false);
        }

        bool isLocked() const noexcept {
            return this->_locked;
        }
        /**
         * @brief Lock or unlock de mode at the controller
         * 
         * @param locked State of the mode lock
         */
        void setLocked(bool locked) noexcept {
            this->setAnalogEnabled(this->_analog, locked);
        }

        /**
         * @brief Executes a command at the controller
         * 
         * @tparam SIZE The size of the command
         * @param command The command string for the controller to execute
         * @return const std::array<uint8_t, 21>&  The return value from the controller
         */
        template<size_t SIZE>
        const std::array<uint8_t, 21>&  executeCommand(const std::array<uint8_t, SIZE>& command) {
            this->_bus.write_and_read(this->_select, command.max_size(), command.data(), this->_defaultBuffer.data());
            return this->_defaultBuffer;
        }

    private:
        Ps2Bus& _bus;
        hwlib::pin_out& _select;
        uint_fast16_t _buffer;
        uint_fast8_t  _hwlibBuffer;
        std::array<uint8_t, 21> _defaultBuffer;

        bool _analog;
        bool _config;
        bool _locked;
        
        const std::array<uint8_t, 21> _pollCommand = {
            0x01, //0
            0x42, //1
            0x00, //2
            0x00, //3
            0x00, //4
            0x00, //5
            0x00, //6
            0x00, //7
            0x00, //8
            0x00, //9
            0x00, //10
            0x00, //11
            0x00, //12
            0x00, //13
            0x00, //14
            0x00, //15
            0x00, //16
            0x00, //17
            0x00, //18
            0x00, //19
            0x00  //20
        };
        const std::array<uint8_t, 9> _readGamepadCommand = {
                0x01,
                0x42,
                0x00,
                0x00,
                0x00,
                
                0x00,
                0x00,
                0x00,
                0x00
            };
        const std::array<uint8_t, 5> _enterConfigCommand = {
            0x01,0x43,0x00,0x01,0x00
        };
        const std::array<uint8_t, 9> _exitConfigCommand = {
            0x01,0x43,0x00,0x00,0x5A,0x5A,0x5A,0x5A,0x5A
        };

        std::array<uint8_t, 9> _setModeCommand = {
            0x01,
            0x44,
            0x00,
            0x00, // 0x01 for analog mode// analog ? uint8_t(0x01) : uint8_t(0x00),
            0x00, // 0x03 for lock on current mode locked ? uint8_t(0x03) : uint8_t(0x00),
            0x00,
            0x00,
            0x00,
            0x00
        };
        const std::array<uint8_t, 9> _getStatusCommand {
            0x01,
            0x45,
            0x00,
            0x5A,
            0x5A,
            0x5A,
            0x5A,
            0x5A,
            0x5A
        };
        std::array<uint8_t, 9> _enableAllButtonsCommand  = {
            0x01,0x4F,0x00,0xFF,0xFF,0x03,0x00,0x00,0x00
        };
    };
}

#endif