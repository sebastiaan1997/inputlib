#ifndef GAMELIB_GAME_OBJECT_HPP
#define GAMELIB_GAME_OBJECT_HPP

#include "drawable.hpp"
#include "vector.hpp"
#include "events/object-event.hpp"

namespace gamelib {
    class GameObject: public Drawable {
    public:
        GameObject(Vector<unsigned int, 2> position, Vector<unsigned int, 2> size):
            Drawable(position, size),
            _event(nullptr) {}

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
         * @brief Executes everything that must be done in the current tick
         * 
         * @return true Something has changed
         * @return false Nothing has changed
         */
        bool tick() {
            if(this->isActive()){
                return false;
            }
            return this->tickImplementation();
        }


            



    protected:
        /**
         * @brief Implementation of intersecting checking provided by the child classes
         * 
         * @param other The object to check
         * @return true 
         * @return false 
         */
        virtual bool intersectsImplementation(const GameObject& other) const = 0;

        
        virtual bool tickImplementation() = 0;

    private: 
        EventChain<ObjectEventData>* _event;




    };
}

#endif