//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef PACMAN_HPP
#define PACMAN_HPP

#include "game-lib/game-lib.hpp"
#include "wrap-hwlib.hpp"
#include "eat-listener.hpp"
template<unsigned int TARGET_SIZE = 0>
class Pacman: public gamelib::GameObject {

public:
    Pacman(): gamelib::GameObject({0,0}, {20, 20}), pac(gamelib::Circle({0,0}, 5)) {}
    
    Pacman(std::array<gamelib::GameObject*, TARGET_SIZE>& targets): 
        gamelib::GameObject({0,0}, {20, 20}), pac(gamelib::Circle({0, 0}, 5)), _targets(targets) {}
    void setListener(EatListener& listener){
        this->_eatListener = &listener;

    }
protected:
    virtual void drawImplementation(hwlib::window& win, hwlib::buffering buff = hwlib::buffering::unbuffered) override {        
        // pac.draw(win, hwlib::buffering::buffered);
        pac.draw(win, hwlib::buffering::buffered);
        if(buff == hwlib::buffering::unbuffered) {
            win.flush();
        }        
    }

    virtual bool tickImplementation() override {
        bool changed = false;
        // hwlib::cout << this->getDirection() << hwlib::flush;
        // this->pac.setPosition({ 0, 0 });
        this->pac.setSize(this->getSize());
        for(GameObject* const target: this->_targets){
            if(gamelib::GameObject::intersects(*target)){
                target->setActive(false);
                changed = true;
            }
        }
        return changed;
    }

    virtual void interactImplementation(gamelib::GameObject& other) override {
        if(this->_eatListener == nullptr) {
            return;
        }
        for(GameObject* const obj: this->_targets) {
            if((&other) == obj) {
                gamelib::ObjectEventData data = { this, &other };
                this->_eatListener->invoke(data);
            }
        }
    }
private:
    gamelib::Circle pac;
    std::array<gamelib::GameObject*, TARGET_SIZE> _targets;
    EatListener* _eatListener = nullptr;
};

#endif