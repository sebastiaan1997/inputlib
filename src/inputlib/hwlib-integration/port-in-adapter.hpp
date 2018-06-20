#ifndef PORT_IN_ADAPTER_HPP
#define PORT_IN_ADAPTER_HPP

#include "../wrap-hwlib.hpp"
#include <array>
#include <


namespace inputlib {
    template<typedef CONTROLLER>
    class PortInAdapter : public hwlib::port_in {
    public:
        virtual uint_fast8_t number_of_pins() {
            return 8;
        }

        PortInAdapter(CONTROLLER controller): _controller(controller) {}

        virtual uint_fast8_t get(hwlib::buffering buff = hwlib::buffering::unbuffered) {
       
        }
        
        virtual void refresh() override {
            
        }        

    private:
        CONTROLLER _slave;
        
    
    };
}
#endif