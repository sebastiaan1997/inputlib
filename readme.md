# Inputlib
Library for inputdevices build on top of WOVO/hwlib

## BMPTK++
The library uses bmptk++, a multi platform cmake based build environment for embedded development

## LGPL 3.0
The library is released with the open-source LGPL 3.0 license. It means that you can use the library in your project without open-sourcing your whole project. It also means that you also can modify the library, but when you do, you have to publish the changed version of the library.

## Arduino DUE
The library is developed and tested for the Arduino DUE.

## GCC Standard C library
Because of the disabled C++ Standard library, some core c++ functions won't work. To solve this, the memset, memcopy & __cxa_pure_virtual are implemented
manually.

## Implemented input
There are already implemented input devices.
* PlayStation 1/2 controller

## Tight intergration
To help as many people as possible, the library integrates as tight as possible with HWLIB (by WOVO) so it can be used by many educational projects at
the Hogeschool Utrecht (University of Applied Sciences Utrecht).


## Building the library

* CMAKE
* Python3
* 