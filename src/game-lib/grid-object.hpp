//          Copyright Sebastiaan Saarloos 2018.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)

#ifndef GAMELIB_GRIDOBJECT_HPP
#define GAMELIB_GRIDOBJECT_HPP

#include "vector.hpp"

namespace gamelib {
    class IGridObject {
        virtual Vector<unsigned int, 2> getGridPosition() const = 0;
    };
}
#endif