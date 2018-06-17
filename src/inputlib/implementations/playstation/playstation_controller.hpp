#pragma once
#include "../../wrap-hwlib.hpp"
#include "../../ps2_bus.hpp"


namespace inputlib {
    
    
    class PlaystationController {
    public:
        PlaystationController(Ps2Bus& bus, hwlib::pin_in& select): _bus(bus), _select(select) {}
        



    private:
        Ps2Bus& _bus;
        hwlib::pin_in& _select;

        
    }

}