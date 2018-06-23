
#include "wrap-hwlib.hpp"
#include "game-lib/game-lib.hpp"
#include <array>
#include "pacman.hpp"


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

      hwlib::wait_ms(500);
    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
    
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
   
    auto display = hwlib::glcd_oled_buffered( i2c_bus, 0x3c );

    // hwlib::graphics_random_circles(display);
    
    display.clear();
    auto pacman = Pacman();

    pacman.setDirection({2, 0});
    hwlib::cout << pacman.getDirection() << hwlib::flush;
    while(true) {
        display.clear();
        pacman.tick();
        pacman.draw(display);
        display.flush();
    }
    return 0;
}



