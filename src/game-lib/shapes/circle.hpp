//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef GAMELIB_CIRCLE_HPP
#define GAMELIB_CIRCLE_HPP

#include "../wrap-hwlib.hpp"
#include "../drawable.hpp"
#include "../vector.hpp"
#include <array>

namespace gamelib {
    
    /**
     * @brief A circle object.
     * @details A circle object that uses the Midpoint Circle Algorithm as described on Wikipedia
     * @auhtor Wikipedia
     * 
     */
    class Circle: public Drawable {
        

    public:
        Circle(Vector<unsigned int, 2> position, unsigned int radius):
            Drawable(position, {radius*2, radius*2 }),
            _radius(radius) {}


        
    protected:
        /**
         * @brief The implementation of drawing a circle
         * @author Wikpedia
         * 
         * @param target The screen to draw to
         */
        virtual void drawImplementation(hwlib::window& target, hwlib::buffering buff = hwlib::buffering::unbuffered) override {
            // Credits to Wikipedia (22 june 2018)
            // URL https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
            auto radius = this->_radius;
            int x = radius-1;
            int y = 0;
            int dx = 1;
            int dy = 1;
            int err = dx - (radius << 1);
            auto x0 = (this->getPosition()[0]) + this->_radius;
            auto y0 = (this->getPosition()[1]) + this->_radius;


            while (x >= y) {
                target.write({x0 + x, y0 + y}, hwlib::buffering::buffered);
                target.write({x0 + y, y0 + x}, hwlib::buffering::buffered);
                target.write({x0 - y, y0 + x}, hwlib::buffering::buffered);
                target.write({x0 - x, y0 + y}, hwlib::buffering::buffered);
                target.write({x0 - x, y0 - y}, hwlib::buffering::buffered);
                target.write({x0 - y, y0 - x}, hwlib::buffering::buffered);
                target.write({x0 + y, y0 - x}, hwlib::buffering::buffered);
                target.write({x0 + x, y0 - y}, hwlib::buffering::buffered);

                if (err <= 0) {
                    y++;
                    err += dy;
                    dy += 2;
                }
                
                if (err > 0) {
                    x--;
                    dx += 2;
                    err += dx - (radius << 1);
                }
            }
            if(buff == hwlib::buffering::unbuffered) {
                target.flush();
            }
        }

        unsigned int getRadius() const noexcept {
            return this->_radius;
        }
        void setRadius(unsigned int radius) noexcept {
            this->_radius = radius;
            this->setSize({radius * 2, radius * 2});
        }
    private:
        /**
         * @brief The radius of the circle
         * 
         */
        unsigned int _radius;
        /**
         * @brief The location
         * 
         */
        Vector<unsigned int, 2> _location;
    };
}
#endif