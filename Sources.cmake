# Libraries:

link_libraries (gcc)

set (hwlib ${build_environment}/libraries/hwlib)
include_directories (${hwlib}/library)

set (catch ${build_environment}/libraries/Catch2)
include_directories (${catch}/single_include)

# Source Files:

# file(GLOB_RECURSE sources src/**/*.hpp src/**/*.cpp src/**/*.h)




set (sources
    src/main.cpp
        src/inputlib/wrap-hwlib.hpp
        src/inputlib/device_interface.hpp
        src/inputlib/input_device.hpp
        src/inputlib/playstation2_controller.hpp
)
