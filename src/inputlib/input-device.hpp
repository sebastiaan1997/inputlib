#ifndef INPUT_DEVICE_HPP
#define INPUT_DEVICE_HPP

#include <cstdint>
#include "wrap-hwlib.hpp"


namespace inputlib {
    
    template<typename BUS_TYPE, typename COMMAND_ADAPTER, typename EVENT_HANDLER = nullptr>
    class InputDevice {
        public:
        InputDevice(BUT_TYPE bus);
        
        



        private:
        BUS_TYPE _bus;



    };
}
#endif