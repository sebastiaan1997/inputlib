#ifndef GAMELIB_DRAWABLE_HPP
#define GAMELIB_DRAWABLE_HPP
#include "vector.hpp"
#include "color.hpp"
#include "wrap-hwlib.hpp"
#include "drawable.hpp"

namespace gamelib{
    /**
     * @brief Base class for all objects used in the game
     * 
     */
    class Drawable {
    public:
        Drawable(Vector<unsigned int, 2> position, Vector<unsigned int, 2> size):
            _size(size), 
            _position(position) {}
        
        /**
         * @brief Get the Size of the game object.
         * 
         * @return const Vector<unsigned int, 2>& 
         */
        const Vector<unsigned int, 2>& getSize() const noexcept{
            return this->_size;
        }
        const Vector<unsigned int, 2>& setSize(Vector<unsigned int, 2> size) noexcept {
            this->_size = size;
            return this->_position;
        }
        const Vector<unsigned int, 2>& getPosition() const noexcept {
            return this->_position;
        }
        const Vector<unsigned int, 2>& setPosition(Vector<unsigned int, 2> position) noexcept {
            this->_position = position;
            return this->_position;
        }


        bool isActive() const noexcept {
            return this->_active;
        }
        void setActive(bool active) noexcept {
            this->_active = active;
        }

        
        Color getBorderColor() const noexcept {
            return this->_borderColor;
        }
        Color setBorderColor(Color borderColor) noexcept {
            this->_borderColor = borderColor;
            return this->_borderColor;
        }

        Color getInnerColor() const noexcept {
            return this->_innerColor;
        }

        Color setInnerColor(Color innerColor) noexcept {
            this->_innerColor = innerColor;
            return this->_innerColor;
        }

    

        void draw(hwlib::window& win) {
            if(!this->_active) {
                return;
            }
            if(this->_size.isZero()){
                return;
            }
            this->drawImplementation(win);
        }

        
        

    protected:
        virtual void drawImplementation(hwlib::window& target) = 0;
        
    private:
        Vector<unsigned int, 2> _size;
        Vector<unsigned int, 2> _position;
        Color _borderColor;
        Color _innerColor;
        bool _active;
    };
}

#endif