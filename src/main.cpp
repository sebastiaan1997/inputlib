
#include "wrap-hwlib.hpp"
#include "game-lib/game-lib.hpp"
#include <array>

struct pinset {
    hwlib::target::pin_in data;
    hwlib::target::pin_out command;
    hwlib::target::pin_out attention;
    hwlib::target::pin_out clock;
    hwlib::target::pin_in  acknoledge;
};

typedef hwlib::target::pins duepin ;



int main() {
// Wait for the serial connection to connection
     namespace target = hwlib::target;
      WDT->WDT_MR = WDT_MR_WDDIS;
   
    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
    
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
    auto display = hwlib::glcd_oled_buffered( i2c_bus, 0x3c );  
    constexpr auto buff = hwlib::buffering::buffered;
    

    hwlib::location o(25,25);
    int radius = 5;
    // hwlib::graphics_random_circles(display);
    
    display.clear();
    auto circle1 =  gamelib::Circle({30, 0}, 15);
    auto circle2 =  gamelib::Circle({0, 0}, 10);

    std::array<gamelib::Drawable*, 2> drawables = {
        &circle1,
        &circle2
    };
    
    for(unsigned int i = 0; i < 128 - 30; i++) {
        display.clear();
        for(auto d: drawables) {
            auto pos = d->getPosition();
            d->setPosition({pos[0] + 1, pos[1]});
            d->draw(display);
        }
        display.flush();
    }
    
    display.flush();
    while(true){
        hwlib::wait_ms(1000);
    }



    return 0;
}



