//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#define TEST
#ifdef TEST
#include "inputlib/inputlib.hpp"

bool buttonTest() {
    bool succeed = true;
    using bm = inputlib::ButtonMask;
    inputlib::Ps2TestBus bus;
    auto ss = hwlib::target::pin_out(hwlib::target::pins::d25);
    auto ps = inputlib::PlaystationController(bus, ss);
    ps.init();
    // Disable all buttons
    bus.setButtons(0b0000'0000'0000'0000);
    ps.refresh();
    if(ps.pinButtonDown().get() || ps.pinButtonUp().get() || ps.pinButtonLeft().get() || ps.pinButtonRight().get()) {
        succeed = false;
        hwlib::cout << "One of the direction buttons is true, while it should be false" << hwlib::endl;
    }
    if(ps.pinButtonSquare().get() || ps.pinButtonCircle().get() || ps.pinButtonX().get(), ps.pinButtonTriangle().get()){
        succeed = false;
        hwlib::cout << "One of the action buttons is true, while it should be false" << hwlib::endl;
    }
    bus.setButtons(0b1111'1111'1111'1111);

    if(!ps.pinButtonDown().get() || !ps.pinButtonUp().get() || !ps.pinButtonLeft().get() || !ps.pinButtonRight().get()) {
        succeed = false;
        hwlib::cout << "One of the direction buttons is false, while it should be true" << hwlib::endl;
    }
    if(!ps.pinButtonSquare().get() || !ps.pinButtonCircle().get() || !ps.pinButtonX().get(), !ps.pinButtonTriangle().get()){
        succeed = false;
        hwlib::cout << "One of the action buttons is false, while it should be true" << hwlib::endl;
    }

    
    return succeed;
}
/**
 * @brief Test for handeling analog values
 * 
 * @return true 
 * @return false 
 */
bool analogTest() {
    bool succeed = true;
    hwlib::location result = {0, 0};
    inputlib::Ps2TestBus bus;
    auto ss = hwlib::target::pin_out(hwlib::target::pins::d25);
    inputlib::PlaystationController ps(bus, ss);
    ps.init();
    bus.setLeftJoyStick(0,0);
    result = ps.getLeftJoystick();
    if(result.x != 0 || result.y != 0){
        succeed = false;
        hwlib::cout << "1 => Value of left joystick should be {0,0}, is instead {" << result.x << ',' << result.y << '}' << hwlib::endl;
    }


    bus.setLeftJoyStick(255, 255);
    result = ps.getLeftJoystick();
    if(result.x != 255 || result.y != 255){
        succeed = false;
        hwlib::cout << "1 => Value of left joystick should be {255,255}, is instead {" << result.x << ',' << result.y << '}' << hwlib::endl;
    }

    bus.setLeftJoyStick(100, 200);
    result = ps.getLeftJoystick();
    if(result.x != 100 || result.y != 200){
        succeed = false;
        hwlib::cout << "1 => Value of left joystick should be {100,200}, is instead {" << result.x << ',' << result.y << '}' << hwlib::endl;
    }

    // Right
     bus.setRightJoyStick(0,0);
    result = ps.getRightJoystick();
    if(result.x != 0 || result.y != 0){
        succeed = false;
        hwlib::cout << "1 => Value of left joystick should be {0,0}, is instead {" << result.x << ',' << result.y << '}' << hwlib::endl;
    }


    bus.setRightJoyStick(255, 255);
    result = ps.getRightJoystick();
    if(result.x != 255 || result.y != 255){
        succeed = false;
        hwlib::cout << "1 => Value of left joystick should be {255,255}, is instead {" << result.x << ',' << result.y << '}' << hwlib::endl;
    }

    bus.setRightJoyStick(100, 200);
    result = ps.getRightJoystick();
    if(result.x != 100 || result.y != 200){
        succeed = false;
        hwlib::cout << "1 => Value of left joystick should be {100,200}, is instead {" << result.x << ',' << result.y << '}' << hwlib::endl;
    }    
    return succeed;

}


int main(){
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    bool test1 = analogTest();
    hwlib::cout << " Analog test => " << hwlib::boolalpha << test1 << hwlib::endl;
    bool test2 = buttonTest();
    hwlib::cout << " Digital test => " << hwlib::boolalpha << test1 << hwlib::endl;
}

#endif