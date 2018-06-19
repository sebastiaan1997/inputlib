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
    template<typename BUTTON_TYPES>
    class IInputDevice: public hwlib::port_in {
    public:
        /**
        * \brief Get changed input
        * \param button Internal id of the button
        * \param buttonValue Value of the button, 0 is off, 100 is pressed
        * \return True if the input has changed
        */
        virtual bool tryGetChangedInput(uint_fast16_t & button, BUTTON_TYPES& buttonValue) = 0;

        /**
         * \brief Get the value of the changed input
         * \param value The value that has been changed
         * \return True if the input has changed
         */
        virtual bool tryGetChangedInput(CommonInputValue& value) = 0;
        
        
        virtual uint_fast8_t number_of_pins() {
            return 8;
        }

        virtual uint_fast8_t get(
            buffering buf = buffering::unbuffered 
        ) = 0;



    };

}
#endif

