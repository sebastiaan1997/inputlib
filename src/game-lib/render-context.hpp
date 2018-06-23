#ifndef GAMELIB_RENDER_CONTEXT_HPP
#define GAMELIB_RENDER_CONTEXT_HPP
#include "drawable.hpp"
#include "wrap-hwlib.hpp"

namespace gamelib{
    template<unsigned int SIZE, bool BOUND_CHECKING = true>
    class RenderContext {
        public:
            #ifndef DOXYGEN
            /**
             * @brief Default contstructor for RenderContext is not available
             * 
             */
            RenderContext() = delete;
            #endif
            // RenderContext(hwlib::RenderContext& ctx) {}

            RenderContext(hwlib::window& window): 
                _window(window),
                _targets(std::array<Drawable&, SIZE>()) {}
            /**
             * @brief Get a object by index
             * 
             * @param index The index to search for
             * @return Drawable& The drawable at the given index
             */
            Drawable& operator[](unsigned int index) {
                return this->_targets[index];
            }
            void operator += (Drawable& drawable) {
                if constexpr (BOUND_CHECKING) {
                    if(this->_targets.size() >= this->_targets.max_size()) {
                        return;
                    }
                }
                this->_targets += drawable;                
            }

            void operator -= (Drawable& drawable) {
                for(unsigned int i =  0; i < this->_targets.size(); i++) {
                    this->_   
                }
            }

            void render() {
                for(Drawable& drawable: this->_targets) {
                    drawable.draw(this->_window);
                }
                this->_window.flush();
            }
    private:
        hwlib::window& _window;
        std::array<Drawable&, SIZE> _targets;
    };
}

#endif