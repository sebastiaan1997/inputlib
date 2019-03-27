//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)
#ifndef GAMELIB_EVENTS_OBJECT_LISTENER_HPP
#define GAMELIB_EVENTS_OBJECT_LISTENER_HPP
#include "../game-object.hpp"
#include "listener.hpp"

namespace gamelib {
    /**
     * @brief Default event data
     * 
     */
    struct ObjectEventData {
        /**
         * @brief The object that is launching the event
         * 
         */
        gamelib::GameObject* const current;
        /**
         * @brief The object that is involved in the event
         * 
         */
        gamelib::GameObject* const target;
    };
    typedef Listener<ObjectEventData> ObjectListener;
}
#endif