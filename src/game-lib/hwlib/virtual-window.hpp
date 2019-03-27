//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)



#ifndef GAMELIB_VIRTUAL_WINDOW_HPP
#define GAMELIB_VIRTUAL_WINDOW_HPP
#include "../wrap-hwlib.hpp"
#include <array>

namespace gamelib {
    /**
     * @brief Window decorator to correct some drawings by moving them and limiting the space to draw
     * 
     */
    class VirtualWindow: public hwlib::window{
    public:
        /**
         * @brief Copy constructor
         * 
         * @param copy Item to make a copy from
         */
        VirtualWindow(const VirtualWindow& copy): 
            hwlib::window(copy.size, copy.foreground, copy.background), _slave(copy._slave), _position(copy._position) { }
        /**
         * @brief Construct a new Virtual Window object with default size
         * 
         * @param window The window to draw to
         * @param location The position relative to the left upper corner
         */
        VirtualWindow(hwlib::window& window, hwlib::location location): 
            hwlib::window(window.size, window.foreground, window.background), _slave(window), _position(location) {}
        /**
         * @brief Construct a new Virtual Window object
         * 
         * @param window 
         * @param location 
         * @param size 
         */
        VirtualWindow(hwlib::window& window, hwlib::location location, hwlib::location size):
            hwlib::window(size, window.foreground, window.background),
            _slave(window),
            _position(location) { }

        /**
         * @brief Get the position of the virtual window relative to the slave window
         * 
         * @return hwlib::location
         */
        const hwlib::location& getPosition() const noexcept{
            return this->_position;
        }
        /**
         * @brief Set the Position object
         * 
         * @param position 
         */
        void setPosition(const hwlib::location& position) {
            this->_position = position;
        }
        /**
         * @brief Construct a new write object
         * 
         * @param location The location to write to
         * @param buff Type of buffering
         */
        virtual void write_implementation(hwlib::location location, hwlib::color color, hwlib::buffering buff = hwlib::buffering::unbuffered) override {
            if(location.x > this->size.x || location.x < 0) {
                return;
            }
            if(location.y > this->size.y || location.y < 0) {
                return;
            }
            this->_slave.write({location.x + this->getPosition().x, location.y + this->getPosition().y}, color, buff);
        }
        /**
         * @brief Flush to the real window
         * 
         */
        virtual void flush() override {
            this->_slave.flush();   
        }

        


    private:
        hwlib::window& _slave;
        hwlib::location _position;


    };
}
#endif