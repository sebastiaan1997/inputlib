//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef GAMELIB_LINE_HPP
#define GAMELIB_LINE_HPP

#include  "../wrap-hwlib.hpp"
#include "../drawable.hpp"
#include "../vector.hpp"

namespace gamelib {
    class Line: public Drawable {
    public:
        Line(Vector<unsigned int, 2> start, Vector<unsigned int, 2> end): Drawable(start, end) {}
    protected:
        virtual void drawImplementation(hwlib::window& win, hwlib::buffering buff = hwlib::buffering::unbuffered) override {
            auto start = this->getPosition();
            auto end = this->getSize();
            
            if(start[0] == end[0]){
                return this->drawOnY(win, buff);
            }
            if(start[1] == end[1]){
                return drawOnX(win, buff);
            }
            else {
                return drawSlope(win, buff);
            }
        }
        void drawOnY(hwlib::window& win, hwlib::buffering buff = hwlib::buffering::unbuffered) {
            auto x = this->getPosition()[0];
            for(auto y = this->getPosition()[1]; y < this->getSize()[1]; y++) {
                win.write(hwlib::location(x, y), hwlib::buffering::buffered);
            }
        }
        void drawOnX(hwlib::window& win, hwlib::buffering buff = hwlib::buffering::unbuffered){
            auto y = this->getPosition()[1];
            for(auto x = this->getPosition()[0]; x < this->getSize()[0]; x++) {
                win.write(hwlib::location(x, y), hwlib::buffering::buffered);
            }
        }

        void drawSlope(hwlib::window& win, hwlib::buffering buff = hwlib::buffering::unbuffered){
            auto start = this->getPosition();
            auto end   = this->getSize();
            auto startX = start[0];
            auto endX = end[0];
            auto startY = start[1];
            auto endY =   end[1];
            auto xDiff = int(endX) - int(startX);
            auto yDiff = int(endY) - int(startY);
            hwlib::cout << "startY" << startY << " | endY" << endY << hwlib::endl << hwlib::flush;
            hwlib::cout << "xDiff => " << xDiff << " | yDiff => " << yDiff << hwlib::endl << hwlib::flush;

            auto slope = (yDiff*100) / (xDiff);
            for(unsigned int x = startX; x < endX; x++){
                hwlib::cout << slope << "-" << ((x * slope)/100) << hwlib::endl << hwlib::flush;
                win.write({x, ((x * slope)/100)}, hwlib::buffering::buffered);
            }
        }


    };
}

#endif