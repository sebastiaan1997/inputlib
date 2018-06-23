#ifndef EVENTS_EVENT_CHAIN_HPP
#define EVENTS_EVENT_CHAIN_HPP
#include "listener.hpp"
#include "../game-object.hpp"
namespace gamelib {
    /**
     * @brief A chain of listeners that can be invoked to handle an event
     * 
     * @tparam E Type of data to pass trough the events
     */
    template<typename E>
    class EventChain final{
    public:
        /**
         * @brief Default constructor
         * 
         */
        EventChain(): _next(nullptr), _listener(nullptr) {}
        /**
         * @brief Constructs a new node of an event chain with no next node
         * 
         * @param event The event that will be executed when the constructed node will be invoked
         */
        EventChain(Listener<E>& event): _next(nullptr), _listener(&event) {}
        /**
         * @brief Constructs a new node of an event chain with next node
         * 
         * @param event 
         * @param next 
         */
        EventChain(Listener<E>& event, EventChain<E>& next): _next(&next), _listener(&event) {}
        EventChain(Listener<E>* event, EventChain<E>* next = nullptr): _next(next), _listener(event)  {}
        /**
         * @brief Returns the next node of the event chain
         * 
         * @return EventChain& The next node of the event cain
         */
        EventChain<E>& next() const noexcept {
            if(this->_next == nullptr) {
                // TODO Fix nulltpr to reference
            } 
            return *this->_next;
        }
        /**
         * @brief Returns the event of the current node of the event chain
         * 
         * @return Event& The event of the current node of the event chain
         */
        Listener<E>& listener() const noexcept {
            // TODO Fix nullptr to reference
            return *this->_listener;
        }
        /**
         * @brief Invokes the eventchain, first in will be first executed
         * 
         * @param target The target of the event
         */
        void invoke(E& target) {
            EventChain<E>* current = this;
            while(current != nullptr) {
                if(current->_listener != nullptr){
                    current->_listener->invoke(target);
                }
                current = current->_next;
            }
        }

        void operator() (E& target)  {
            this->invoke(target);
        }
        /**
         * @brief Adds a listener to the event chain
         * 
         * @param listener The listener to add to the event chain
         */
        void operator += (Listener<E>& listener) {
            return this->addListener(listener);
        }

        void addListener(Listener<E>& listener) {
            EventChain<E>* current = this;
            while(current->_next != nullptr) {
                current = this->_next;
            }
            auto a = EventChain<E>(listener);
            current->_next = & a;
        }

    private:
        /**
         * @brief Next node in the event chain, nullptr if absent
         * 
         */
        EventChain< E >* _next;
        /**
         * @brief Listener that is linked to the current event
         * 
         */
        const Listener<E>* _listener;

    };
}

#endif