#pragma once
#include "wrap-hwlib.hpp"


class PinInEvent {
    void operator() (const hwlib::pin_in& pin, bool value) {

    }

    virtual void call(const hwlib::pin_in& pin, bool value) = 0;
};