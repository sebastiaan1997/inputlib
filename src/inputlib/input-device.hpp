#ifndef INPUT_DEVICE_HPP
#define INPUT_DEVICE_HPP

#include <cstdint>
#include "wrap-hwlib.hpp"


namespace inputlib {
    
    template<typename BUS_TYPE, typename DEVICE_POLICY, typename EVENT_HANDLER = nullptr>
    class InputDevice: protected DEVICE_POLICY {
        public:
        InputDevice(BUT_TYPE bus);


        T getAll() const noexcept {
            bus.read_write_bytes();
        }

        template<>
        T getValue() const noexcept {
            
        }

        


        




        

        
        



        private:
        BUS_TYPE _bus;



    };
}
#endif