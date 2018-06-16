//
// Created by sebastiaan on 12-6-18.
//

#ifndef IINPUT_DEVICE_HPP
#define IINPUT_DEVICE_HPP

#include "wrap-hwlib.hpp"



namespace inputlib{
    /**
     * \brief Common interface for all input devices
     * \tparam BUTTON_TYPES Enum with all common buttons of the input type
     */

    class IInputDevice {
    public:

        /**
        * \brief Get changed input
        * \param button Internal id of the button
        * \param buttonValue Value of the button, 0 is off, 100 is pressed
        * \return True if the input has changed
        */
        virtual bool tryGetChangedInput(uint_fast16_t & button, BUTTON_TYPES& buttonValue);

        /**
         * \brief Get the value of the changed input
         * \param value The value that has been changed
         * \return True if the input has changed
         */
        virtual bool tryGetChangedInput(CommonInputValue& value);
    };

}
#endif

