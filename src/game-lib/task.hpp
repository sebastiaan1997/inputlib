//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GAMELIB_TASK_HPP
#define GAMELIB_TASK_HPP
namespace {
    /**
     * @brief Interface that is used for task scheduling
     */
    class ITask {
        /**
         * @brief Method to execute with each iteration
         * 
         */
        virtual void tick() noexcept;
    };

}
#endif