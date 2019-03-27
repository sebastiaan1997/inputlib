//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef EAT_LISTENER_HPP
#define EAT_LISTENER_HPP
#include "candy.hpp"
#include "game-lib/game-lib.hpp"
class EatListener: public gamelib::ObjectListener {
    virtual void invokeImplementation(gamelib::ObjectEventData& obj) {
        obj.target->setActive(false);
        points++;
    }
public:
    unsigned int points = 0;
};
#endif