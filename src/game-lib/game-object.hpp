#ifndef GAMELIB_GAME_OBJECT_HPP
#define GAMELIB_GAME_OBJECT_HPP



#include "drawable.hpp"
#include "vector.hpp"
#include "events/listener.hpp"
#include "events/object-listener.hpp"
#include "events/event-chain.hpp"

namespace gamelib {
    /**
     * @brief The base object for all object used with the gamelib game library
     * 
     */
    class GameObject: public Drawable {
    public:
        GameObject(Vector<unsigned int, 2> position, Vector<unsigned int, 2> size):
            Drawable(position, size),
            _interectionEventChain(EventChain<ObjectEventData>()),
            _direction({0,0}) {}

        
        /**
         * @brief Returns if the GameObject intersects with another GameObject
         * 
         * @param other The object to check
         * @return true The Object intersects with another object
         * @return false The Object intersects doesn't intersect with another ojbect
         */
        bool intersects(const GameObject& other) const {
            if(!this->isActive()) {
                return false;
            }
            if(!other.isActive()) {
                return false;
            }
            
            return this->intersectsImplementation(other);
        }

        /**
         * @brief Executes everything that must be done in the current tick.
         * 
         * @details Will not execute when the object is not active
         * 
         * @return true Something has changed
         * @return false Nothing has changed
         */
        bool tick() {
            if (!this->isActive()){
                return false;
            }
            Vector<unsigned int, 2> pos = this->getPosition();
            pos += this->_direction;
            this->setPosition(pos);
            hwlib::cout << this->getPosition() << hwlib::endl;


            return (this->tickImplementation() && !this->_direction.isZero());

        }

        void addIntersectListener(Listener<ObjectEventData>& listener){
            this->_interectionEventChain += listener;
        }
        /**
         * @brief Get the Direction object, the direction is the movement in pixels per tick
         * 
         * @return Vector<int, 2> The direction
         */
        inline Vector<int, 2> getDirection() const noexcept {
            return this->_direction; 
        }
        /**
         * @brief Sets the direction of this object, the direction is the movement of the current object in pixels per tick
         * @details If the direction is {0,0} the object will not move
         * 
         * @param value The value of the direction
         */
        inline void setDirection(Vector<int, 2> value) noexcept {
            this->_direction = value;
        }

        inline void stop() {
            this->setPosition({0,0});
        }


    protected:
        /**
         * @brief Implementation of intersecting checking provided by the child classes
         * 
         * @param other The object to check
         * @return true The object intersects with the other object
         * @return false The object does not interect with the other object
         */
        virtual bool intersectsImplementation(const GameObject& other) const = 0;

        /**
         * @brief Implementation of a tick cycle provided by the child
         * 
         * @return true Something is changed 
         * @return false Nothing has changed
         */
        virtual bool tickImplementation() = 0;

    private: 
        EventChain<ObjectEventData> _interectionEventChain;
        Vector<int, 2> _direction;



    };
}

#endif