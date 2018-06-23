#ifndef PACMAN_HPP
#define PACMAN_HPP
#include "game-lib/game-lib.hpp"
#include "wrap-hwlib.hpp"
class Pacman: public gamelib::GameObject {
public:
    Pacman(): gamelib::GameObject({0,0}, {20, 20}), pac(gamelib::Circle({0,0}, 5)) {}
    
protected:
    void drawImplementation(hwlib::window& win) override {
        pac.draw(win);
    }
    bool tickImplementation() override {
        hwlib::cout << this->getDirection() << hwlib::flush;
        this->pac.setPosition(this->getPosition());
        return false;
    }
    virtual bool intersectsImplementation(const GameObject& other) const  {
        
        
        return true;
    }
    
private:
    gamelib::Circle pac;



};

#endif