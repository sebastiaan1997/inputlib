//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef INPUTLIB_IMPLEMENTATIONS_PLAYSTATION_BUTTONMASKS 
#define INPUTLIB_IMPLEMENTATIONS_PLAYSTATION_BUTTONMASKS
namespace inputlib {
    enum class ButtonMask: uint16_t {
        SELECT      = 0X00'01,
        L3          = 0X00'02,
        R3          = 0X00'04,
        START       = 0X00'08,
        UP          = 0X00'10,
        RIGHT       = 0X00'20,
        DOWN        = 0X00'40,
        LEFT        = 0X00'80,
        L2          = 0X01'00,
        R2          = 0X02'00,
        L1          = 0X04'00,
        R1          = 0X08'00,
        TRIANGLE    = 0X10'00,
        CIRCLE      = 0X20'00,
        EX          = 0X40'00,
        SQUARE      = 0X80'00
    };
}
#endif