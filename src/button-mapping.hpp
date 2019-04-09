//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef INPUTLIB_BUTTON_MAPPING_HPP
#define INPUTLIB_BUTTON_MAPPING_HPP
namespace inputlib {
    /**
     * @brief Common button mapping interface for inputlib Game-Controller devices
     */
    class ButtonMapping {
    public:
        const bool leftBumperTop;
        const bool leftBumperDown;

        const bool rightBumperTop;
        const bool rightBumperDown;

        const bool analogLeftPressed;
        const bool analogRightPressed;

        const bool up;
        const bool right;
        const bool down;
        const bool left;

        const bool actionTop;
        const bool actionRight;
        const bool actionBottom;
        const bool actionLeft;
    };
};


#endif