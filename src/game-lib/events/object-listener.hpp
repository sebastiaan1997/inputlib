#ifndef GAMELIB_EVENTS_OBJECT_LISTENER_HPP
#define GAMELIB_EVENTS_OJBECT_LISTENER_HPP
#include "../game-object.hpp"
#include "listener.hpp"

namespace gamelib {
    struct ObjectEventData {
        GameObject& current;
        GameObject& target;
    };
    typedef Listener<ObjectEventData> ObjectListener;
}
#endif