#ifndef PS2_POLICY_HPP
#define PS2_POLICY_HPP

#include <cstdint>
#include "../controller-input.hpp"

namespace inputlib {
    class PS2Controller {
        protected:
        /**
         * @brief Datatype used to store the information
         * 
         */
        typedef uint_fast16_t T;


        /**
         * @brief The number of buttons that is used for the button
         * 
         * @return constexpr unsigned int 
         */
        constexpr T buttonCount() const {
            return 16;
        }
        template<ControllerButtons TARGET>
        constexpr T buttonMask() const noexcept {
            return 0x00;
        }

        template<>
        constexpr T buttonMask<ControllerButtons::action_up>() const noexcept{
            return 0x0F;
        }

        constexpr bool invertedInput() const noexcept {
            return false;
        }

        



    };
}

#endif