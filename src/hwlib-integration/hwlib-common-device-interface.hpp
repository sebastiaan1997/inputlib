#ifndef INPUTLIB_HWLIB_INTEGRATION_HWLIB_COMMON_DEVICE_INTERFACE_HPP
#define INPUTLIB_HWLIB_INTEGRATION_HWLIB_COMMON_DEVICE_INTERFACE_HPP
#include "../wrap-hwlib.hpp"
#include "virtual-pin-in.hpp"
namespace inputlib {
    class IHwlibCommonDeviceInterface {
    public:
        virtual VirtualPinIn<uint_fast16_t>& getDirectionUp()    = 0;
        virtual VirtualPinIn<uint_fast16_t>& getDirectionRight() = 0;
        virtual VirtualPinIn<uint_fast16_t>& getDirectionDown()  = 0;
        virtual VirtualPinIn<uint_fast16_t>& getDirectionLeft()  = 0;

        virtual VirtualPinIn<uint_fast16_t>& getActionTop()    = 0;
        virtual VirtualPinIn<uint_fast16_t>& getActionRight()  = 0;
        virtual VirtualPinIn<uint_fast16_t>& getActionBottom() = 0;
        virtual VirtualPinIn<uint_fast16_t>& getActionLeft()  = 0;

        virtual void refresh() = 0;
        
    };
}
#endif