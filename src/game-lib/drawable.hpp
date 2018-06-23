#ifndef GAMELIB_DRAWABLE_HPP
#define GAMELIB_DRAWABLE_HPP
#include "vector.hpp"
#include "color.hpp"
#include "wrap-hwlib.hpp"
#include "drawable.hpp"

namespace gamelib{
    /**
     * @brief Base class of all Drawable objects in the gamelib library
     * 
     */
    class Drawable {
    public:
        Drawable(Vector<unsigned int, 2> position, Vector<unsigned int, 2> size):
            _size(size), 
            _position(position),
            _active(true) {}
        
        /**
         * @brief Get the Size of the game object.
         * 
         * @return const Vector<unsigned int, 2>& 
         */
        const Vector<unsigned int, 2>& getSize() const noexcept{
            return this->_size;
        }
        /**
         * @brief Sets the size of the object
         * 
         * @param size The new size of the object
         */
        void setSize(Vector<unsigned int, 2> size) noexcept {
            this->_size = size;
        }

        /**
         * @brief Gets the current position of the object
         * 
         * @return const Vector<unsigned int, 2>& 
         */
        const Vector<unsigned int, 2>& getPosition() const noexcept {
            return this->_position;
        }
        const Vector<unsigned int, 2>& setPosition(Vector<unsigned int, 2> position) noexcept {
            this->_position = position;
            return this->_position;
        }
        /**
         * @brief Returns if the object is activated or not
         * 
         * @return true The object is activated
         * @return false The object is not activated
         */
        bool isActive() const noexcept {
            return this->_active;
        }
        /**
         * @brief Set the Active object
         * 
         * @param active 
         */
        void setActive(bool active) noexcept {
            this->_active = active;
        }

        /**
         * @brief Gets the border color of the object
         * 
         * @return Color 
         */
        Color getBorderColor() const noexcept {
            return this->_borderColor;
        }
        /**
         * @brief Set the Border Color object
         * 
         * @param borderColor The new border color of the object
         */
        void setBorderColor(Color borderColor) noexcept {
            this->_borderColor = borderColor;
        }
        /**
         * @brief Get the Inner Color object, the color that the object is filled with
         * 
         * @return Color The inner colorm of the object
         */
        Color getInnerColor() const noexcept {
            return this->_innerColor;
        }

        /**
         * @brief Sets the Inner Color object. The color of the object will be ajusted.
         * 
         * @param innerColor The new innercolor of the object
         */
        void setInnerColor(Color innerColor) noexcept {
            this->_innerColor = innerColor;
        }

        /**
         * @brief Draws the object to the given window target. If the object is not active, it will not be drawn
         * 
         * @param target The window target to draw to
         */
        void draw(hwlib::window& target) {
            // If the window is not active, it will not be drawn
            if(!this->_active) {
                return;
            }
            // If the size is 0, the object is invisible so it would be useless to draw it
            if(this->_size.isZero()){
                return;
            }
            this->drawImplementation(target);
        }

        
        

    protected:
        /**
         * @brief Draw implementation provided by the child class
         * 
         * @param target The window target to draw to
         */
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