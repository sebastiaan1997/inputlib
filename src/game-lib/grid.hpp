//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)


#ifndef GAMELIB_GRID_HPP
#define GAMELIB_GRID_HPP
template<unsigned int WIDTH = 20, unsigned int HEIGHT = 20>
    class Grid;

#include <cstdint>
#include <array>
#include "hwlib/virtual-window.hpp"
#include "game-object.hpp"

namespace gamelib {
    /**
     * @brief A grid, can be used as base for most retro/arcade games
     * 
     * @details
     * Most of the retro and arcade games use a grid.
     * This class allows you to put normal GameObjects in a grid.
     * This class modifies their behaviour by customizing the draw area
     * of game objects and managing their positions and sizes
     * 
     * 
     * @tparam WIDTH The width of the grid 
     * @tparam HEIGHT The height of the grid
     */
    template<unsigned int WIDTH = 20, unsigned int HEIGHT = 20>
    class Grid {
    
    public:
        /**
         * @brief Default constructor for the Grid Object
         * 
         * @details
         * Default values for the object
         * The grid will be empty
         * The display scale will be 1
         * The position will be 0,0
         * The cell size will be ( 5, 5 )
         * 
         */
        Grid(): _grid({}), _grid2({}), _displayScale(1), _position({0,0}), _cellSize({5,5}) {

            this->clear();

        }
        /**
         * @brief Construct a new Grid object
         * 
         * @param grid 
         * @param position 
         * @param cellSize 
         * @param displayScale 
         */
        Grid(std::array<unsigned int, WIDTH * HEIGHT> grid, Vector<unsigned int, 2> position, Vector<unsigned int, 2> cellSize, unsigned int displayScale = 1):
            _grid(grid), _displayScale(displayScale), _position(position), _cellSize(cellSize) {
                this->clear();
            }
        /**
         * @brief Construct a new Grid object
         * 
         * @param copy 
         */
        Grid(Grid& copy): _grid(copy._grid), _displayScale(copy._displayScale), _position(copy._position){ 
            this->clear();
        }        /**
         * @brief Returns the width of the grid (is the same as the WIDTH template argument)
         * 
         * @return constexpr unsigned int 
         */
        constexpr unsigned int width() const noexcept  {
            return WIDTH;
        }
        /**
         * @brief Returns the height of the grid (is the same as the HEIGHT template arugment)
         * 
         * @return constexpr unsigned int 
         */
        constexpr unsigned int height() const noexcept {
            return HEIGHT;
        }
        /**
         * @brief Executes all related tasks for this iteration
         * 
         * @details
         * Executes all related, recurring tasks that must be done during a iteration.
         * It executes some grid tasks and executes all tasks of it's childeren .
         * 
         * It also 
         * 
         */
        void tick() {
          for(unsigned int y = 0; y < HEIGHT; y++){
                for(unsigned int x = 0; x < WIDTH; x++){
                    GameObject* objPtr = this->getCell(x, y);
                    if(objPtr == nullptr) {
                        continue;
                    }
                    
                    objPtr->tick();
                    objPtr->setPosition({x, y});
                    
                    


                    //objPtr->setPosition({0,0});
                }
            }
            for(unsigned int y = 0; y < HEIGHT; y++){
                for(unsigned int x = 0; x < WIDTH; x++){
                    GameObject* objPtr = this->getCell(x, y);
                    if(objPtr == nullptr) {
                        
                        continue;
                    }
                    auto direction = objPtr->getDirection();
                    if(direction[0] != 0 || direction[1] != 0){
                        if(this->setCell(direction[0] + x, direction[1] + y, objPtr, true, true)){
                            this->setCell(x, y, nullptr);
                        }
                    }
                }
            }
        }
        /**
         * @brief Flushes the changes to the main buffered
         * 
         * @details
         * The grid class contains 2 arrays. 1 to keep changes, 1 that will be queried.
         * If a transaction of changes is done, the flush method can be called to apply the changes to the grid.
         * It ovewrites the main grid by the buffer.
         * 
         */
        void flush(){
            for(unsigned int i = 0; i < this->_grid.max_size(); i++) {
                if(this->_grid2[i] == nullptr) {
                    this->_grid[i] = nullptr;
                }
                else{
                    this->_grid[i] = this->_grid2[i];
                }
            }
        }
        /**
         * @brief Removes all objects from the grid
         * 
         */
        void clear(){
            for(unsigned int i = 0; i < this->_grid.max_size(); i++) {
                this->_grid[0] = nullptr;
                this->_grid2[0] = nullptr;
            }
        }

        /**
         * @brief Draws the grid, with childeren to the target.
         * 
         * @param target The target to draw to
         * @param buff The type of buffering that is used
         */
        void draw(hwlib::window& target, hwlib::buffering buff = hwlib::buffering::buffered) {
            if(this->_cacheChanged) {
                this->flush();
            }

            auto size = hwlib::location({ this->_cellSize[0], this->_cellSize[1] });
            VirtualWindow vWindow(target, {0,0}, size);
            for(unsigned int y = 0; y < HEIGHT; y++){
                for(unsigned int x = 0; x < WIDTH; x++){
                    GameObject* objPtr = this->getCell(x, y);
                    if(objPtr != nullptr){
                        auto loc = hwlib::location({
                            x * this->_displayScale * this->_cellSize[0] + this->_position[0], 
                            y * this->_displayScale * this->_cellSize[1] + this->_position[1]}
                        );
                        
                        objPtr->setSize({size.x, size.y});
                        objPtr->setPosition({ 0, 0 });
                        
                        vWindow.setPosition(loc);
                        objPtr->draw(vWindow, hwlib::buffering::buffered);
                        objPtr->setPosition({x, y});
                        objPtr->setSize({1, 1});
                    }
                }
            }
            target.flush();
        }
        /**
         * @brief Try and get a cell value
         * 
         * @details
         * Tries to get a value from the grid.
         * If a value is not present, the cell will contain a nullptr
         * Otherwise it will contain a pointer to the target object.
         * So if a value is present, it will write the value to the value reference parameter
         * and return true, otherwise it will return false and will not do anything.
         * 
         * @param x The X coordinate to query
         * @param y The Y coordinate to query
         * @param value The value of the cell
         * @return true The cell contains a valid value
         * @return false The cell contains a nullptr
         */
        bool tryGetCell (unsigned int x, unsigned int y, GameObject& value) {
            GameObject* objPtr = this->getCell(x, y);
            if(objPtr == nullptr) {
                return false;
            }
            value = *objPtr;
            return true;
        }
        /**
         * @brief Get a value at a given location
         * 
         * @details
         * Get a value at a given location. If the function returns a nullptr,
         * the cell is empty, otherwise it will return a pointer to a object that
         * is located at the given cell.
         * 
         * @param x The x coordinate to query
         * @param y The y coordinate to query
         * @return GameObject* The value of the cell.
         */
        GameObject* getCell (unsigned int x, unsigned int y) {
            return this->_grid[this->width() * y + x];
        }
        /**
         * @brief Sets a new value at a cell
         * 
         * @param x The x value of the coordinate to write to
         * @param y The y value of the coordinate to write to
         * @param obj The new value that will placed at in the cell
         * @param buffered True, it will write to the buffer, false then it will directly manipulate the grid
         * @return true The command is processed
         * @return false The command is failed
         */
        bool setCell (unsigned int x, unsigned int y, GameObject& obj, bool buffered = true) {
            return this->setCell(x, y, &obj);
        }
        /**
         * @brief Sets a new value at a cell
         * 
         * @param x The x value of the coordinate to write to
         * @param y The y value of the coordinate to write to
         * @param obj The new pointer that will placed at in the cell
         * @param buffered True, it will write to the buffer, false then it will directly manipulate the grid
         * @return true The command is processed
         * @return false The command is failed
         */
        bool setCell (unsigned int x, unsigned int y, GameObject* obj, bool buffered = true, bool event = false) {
            if(x >= WIDTH || y >= HEIGHT) {
                return false;
            }
             if(event){
                hwlib::cout << "Event" << hwlib::endl << hwlib::flush;
                obj->interact(*this->_grid[WIDTH * y + x]);
            }

            if(buffered) {
                this->_grid2[WIDTH * y + x] = obj;
                this->_cacheChanged = true;
            }
            else {
                if(this->_cacheChanged) {
                    this->flush();
                }
                this->_grid[WIDTH * y + x] = obj;
            }
           

            this->_changed = true;
            return true;
        }
        /**
         * @brief Get the display scale.
         * 
         * @details
         * Display scale means the times a pixel from the grid will be mapped to a phisical pixel
         * @return unsigned int 
         */
        unsigned int getDisplayScale() const noexcept {
            return this->_displayScale;
        }
        /**
         * @brief Set the Display Scale object
         * 
         * @param displayScale 
         */
        void setDisplayScale(unsigned int displayScale) {
            if(displayScale == 0) {
                this->_displayScale = 1;
                return;
            }
            this->_displayScale = displayScale;
        }
        /**
         * @brief Get the position at the screen of the grid
         * 
         * @return Vector<unsigned int, 2> 
         */
        Vector<unsigned int, 2> getPosition() const noexcept {
            return this->_position;
        }
        /**
         * @brief Sets the position at the screen
         * 
         * @param position The new value of the position
         */
        void setPosition(Vector<unsigned int, 2> position) noexcept {
            this->_position = position;
        }
        /**
         * @brief Get the size of one cell in pixels
         * 
         * @return Vector<unsigned int, 2> The size of one cell in pixels
         */
        Vector<unsigned int, 2> getCellSize() const noexcept {
            return this->_cellSize;
        }
        /**
         * @brief Set the Cell Size object
         * 
         * @param cellSize 
         */
        void setCellSize(Vector<unsigned int, 2> cellSize)  noexcept {
            if(cellSize[0] == 0 && cellSize[1] == 0) {
                cellSize = { 1, 1 };
            }
            this->_cellSize = cellSize;
            for(GameObject* objPtr: this->_grid) {
                if(objPtr == nullptr) {
                    continue;
                }
                objPtr->setSize(this->_cellSize);
            }
        }


    private:
        std::array<GameObject*, WIDTH * HEIGHT> _grid;
        std::array<GameObject*, WIDTH * HEIGHT> _grid2;
        unsigned int _displayScale;
        Vector<unsigned int, 2> _position;
        Vector<unsigned int, 2> _cellSize;
        bool _changed = false;
        bool _cacheChanged = false;
    };   
}

#endif