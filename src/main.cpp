//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#define LOGGING


#include "wrap-hwlib.hpp"
#include "game-lib/game-lib.hpp"
#include "inputlib/inputlib.hpp"
#include <array>
#include "pacman.hpp"
#include "candy.hpp"
#include "eat-listener.hpp"

// #include "test.cpp"

#ifdef TEST
#include "test.cpp"
#endif

#ifndef TEST

typedef hwlib::target::pins duepin ;
namespace target = hwlib::target;

int main() {
    WDT->WDT_MR = WDT_MR_WDDIS;

    hwlib::wait_ms(1000);

    auto ss = target::pin_out(duepin::d7);
    
    // Ps2Bus(hwlib::pin_out& sclk, hwlib::pin_in& miso, hwlib::pin_out& mosi, hwlib::pin_in& acknolage)
    auto sclk = hwlib::target::pin_out(duepin::d4);
    auto miso = hwlib::target::pin_in(duepin::d12);
    miso.pullup_enable();
    auto mosi = hwlib::target::pin_out(duepin::d2);
    auto led = target::pin_out(duepin::d13);
    
    // Ps2Bus(hwlib::pin_out& sclk, hwlib::pin_in& miso, hwlib::pin_out& mosi, hwlib::pin_in& acknolage
    auto ack = target::pin_in(duepin::d25);
    inputlib::Ps2Bus ps2_bus(sclk, miso, mosi, ack);
    // inputlib::Ps2TestBus ps2_bus;
    
    auto ps_controller = inputlib::PlaystationController(ps2_bus, ss);

    ps_controller.init();
    hwlib::location right = {0,0};
    

    gamelib::Grid<10, 5> grid;

    auto scl = target::pin_oc( target::pins::scl );
    auto sda = target::pin_oc( target::pins::sda );
    
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );
    auto display = hwlib::glcd_oled_buffered( i2c_bus, 0x3c );
    display.clear();
    display.flush();
    

    std::array<Candy, 100> candies = {};
    std::array<gamelib::GameObject*, 100> candyPointer = {nullptr};
    EatListener listener;

    grid.setCellSize({10, 10});
    unsigned int candyIndex = 0;
    for(unsigned int x = 0; x < 10; x++){
        for(unsigned int y = 0; y < 5; y++) {
            grid.setCell(x, y, candies[candyIndex]);
            candyPointer[candyIndex] = &candies[candyIndex];
            candyIndex++;
        }
    }
    
    
    Pacman<100> pac(candyPointer);
    pac.setDirection({1,0});
    pac.setListener(listener);
    // c.setDirection({1, 0});
    // hwlib::cout << c.getDirection() << hwlib::endl <<hwlib::flush;
    hwlib::wait_ms(1000);
    grid.setCell(0, 0, pac);
    auto font    = hwlib::font_default_8x8();
    auto dout = hwlib::window_ostream( display, font );
    grid.draw(display, hwlib::buffering::buffered);
    display.flush();
    hwlib::location left = {0, 0};
    while(true){
        ps_controller.init();
        hwlib::cout << "Read right" << hwlib::endl;
        right = ps_controller.getRightJoystick();
        hwlib::cout << "Read left" << hwlib::endl;
        left  = ps_controller.getLeftJoystick();
        int valueX = 0;

        hwlib::cout << ps_controller.pinButtonLeft().get() << ps_controller.pinButtonRight().get() << ps_controller.pinButtonDown().get() <<hwlib::endl;
        
        if(right.x == 0 || left.x == 255  ||  ps_controller.pinButtonLeft().get()){
            hwlib::cout << "left" << hwlib::endl;
            valueX = -1;
        }
        else if(right.x == 255 || left.x == 0 || ps_controller.pinButtonRight().get()){
            hwlib::cout << "right" << hwlib::endl;
            valueX = 1;
        }
        int valuey = 0;
        if(right.y == 0 || left.y == 255 || ps_controller.pinButtonUp().get()){
            hwlib::cout << "down" << hwlib::endl;
            valuey = -1;
        }
        else if(right.y == 255 || left.y == 0 || ps_controller.pinButtonDown().get()){
            valuey = 1;
            hwlib::cout << "up" << hwlib::endl;
        }
        pac.setDirection({valueX, valuey});
        display.clear();
        grid.tick();
        grid.flush();
        if(valueX != 0 || valuey != 0){
            led.set(true);
            dout << "\t1301" << listener.points;
            if(listener.points > 48) {
                dout << "\t0102" << "You won!!!";
            }
            grid.draw(display, hwlib::buffering::buffered);
            display.flush();
            led.set(false);
            if(listener.points > 48) {
                for(bool l = true; true; l = !l) {
                    led.set(l);
                    hwlib::wait_ms(500);
                }
            }
        }
    }
    return 0;
}
#endif