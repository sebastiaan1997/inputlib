//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef INPUTLIB_IMPLEMENTATIONS_PLAYSTATION_BYTE_MAPPING_HPP
#define INPUTLIB_IMPLEMENTATIONS_PLAYSTATION_BYTE_MAPPING_HPP

#include <cstdint>

namespace inputlib {
    namespace {
        struct PullAllResponse {
            /**
             * @brief Padding at the start of the request
             * 
             */
            const uint8_t startPadding;
            /**
             * @brief Device mode
             * 
             */
            const uint8_t deviceMode;

            const uint8_t p1;
            /**
             * @brief First digital button representation
             * 
             */
            const uint8_t digitalButtons1;
            /**
             * @brief Second digital button representation
             * 
             */
            const uint8_t digitalButtons2;
            /**
             * @brief X-ax value of the right joystick
             * 
             * @details
             * The X-Ax value of the right joystick
             * Starting at 0 for left-end(<=), 255 for the right-end (=>)
             */
            const uint8_t rightJoystickX;
            /**
             * @brief Y-ax value of the right 
             * 
             */
            const uint8_t rightJoystickY;
            /**
             * @brief 
             * 
             */
            const uint8_t leftJoystickX;
            /**
             * @brief 
             * 
             */
            const uint8_t leftJoystickY;

            const uint8_t rightButton;
            
            const uint8_t leftButton;

            const uint8_t upButton;

            const uint8_t downButton;

            const uint8_t triangleButton;

            const uint8_t circleButton;

            const uint8_t exButton;
            
            const uint8_t squareButton;

            const uint8_t leftTopBumper;
            
            const uint8_t rightTopBumper;

            const uint8_t leftBottomBumper;

            const uint8_t rightBottomBumper;
        };
    }
}

#endif