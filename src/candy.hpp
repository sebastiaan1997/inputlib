//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef CANDY_HPP
#define CANDY_HPP
#include "wrap-hwlib.hpp"
#include "game-lib/game-lib.hpp"

class Candy: public gamelib::GameObject{
public:
    Candy(): GameObject({0,0}, {3,3}) {}
    Candy(gamelib::Vector<unsigned int, 2> position) : GameObject(position, {1,1}) {}
    
protected:
    virtual void drawImplementation(hwlib::window& target, hwlib::buffering buff = hwlib::buffering::unbuffered) override {
        auto size = this->getSize();
        auto position = this->getPosition();
       
            target.write({position[0] + size[0] / 2, position[1] + size[1] / 2});    

        
        
    }

    virtual bool tickImplementation() override {
        auto direction = this->getDirection();
        
        return false || (direction[0] == 0 && direction[1] == 0);
    }

    virtual bool intersectsImplementation(const GameObject& other) const override {

        return false;
    }
private:

};
#endif