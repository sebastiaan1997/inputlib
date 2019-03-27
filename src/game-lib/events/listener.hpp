//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GAMELIB_EVENTS_LISTENER_HPP
#define GAMELIB_EVENTS_LISTENER_HPP
#include "../game-object.hpp"

namespace gamelib {
    /**
     * @brief Event  listener base class
     * 
     * @tparam E Type of the event data
     */
    template<typename E>
    class Listener {
    public:
        /**
         * @brief Default constructor, enables listener by default
         * 
         */
        Listener(): _enabled(true) {}
        /**
         * @brief Construct a new Listener object
         * 
         * @param enabled Enables this listener
         */
        Listener(bool enabled): _enabled(enabled) {}
        /**
         * @brief Alias for invoke method
         * 
         * @param obj Eventlistener data
         */
        void operator()(E& obj) {
            return this->invoke(obj);
        }
        /**
         * @brief Invokes the listener, if not active, it will not execute the handler
         * 
         * @param obj Eventlistener data
         */
        void invoke(E& obj) {
            if(!this->_enabled) {
                return;
            }
            this->invokeImplementation(obj);
        }
        /**
         * @brief Returns if the listener is enabled
         * 
         * @return true The listener is enabled, it will be executed
         * @return false The listener is disabled, it will not be executed
         */
        bool isEnabled() const noexcept {
            return this->_enabled;
        }
        /**
         * @brief Change if the listener is enabled, and will be executed
         * 
         * @param value True, the listener will be enabled and will be executed at a event, false it will not execute
         */
        void setEnabled(bool value) noexcept {
            this->_enabled = value;
        }


    protected:
        /**
         * @brief Implementation of the listener provided by the child. Will be executed if the listener is enabled and an event is occured.
         * 
         * @param obj The event information
         */
        virtual void invokeImplementation(E& obj) = 0;
    private:
        bool _enabled;

    };
}
#endif