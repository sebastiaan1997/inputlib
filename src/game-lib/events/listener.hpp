#ifndef GAMELIB_EVENTS_LISTENER_HPP
#define GAMELIB_EVENTS_LISTENER_HPP
#include "../game-object.hpp"

namespace gamelib {
    template<typename E>
    class Listener {
    public:
        Listener(): _enabled(true) {}
        Listener(bool enabled): _enabled(enabled) {}

        void operator()(E& obj) {
            return this->invoke(obj);
        }
        void invoke(E& obj) {
            if(!this->_enabled) {
                return;
            }
            this->invokeImplementation(obj);
        }

        bool isEnabled() const noexcept {
            return this->_enabled;
        }
        void setEnabled(bool value) noexcept {
            this->_enabled = value;
        }


    protected:
        virtual void invokeImplementation(E& obj) = 0;
    private:
        bool _enabled;

    };
}
#endif