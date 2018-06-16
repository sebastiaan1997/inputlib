#include "wrap-hwlib.hpp"

int main() {
    // Wait for the serial connection to connect
    hwlib::wait_ms(500);

    uint_fast8_t command_script[] = {
            0x00,
            0x01, // New packet
            0x41, // Command
            0xFF, // Mode (Analog/Digital)
            0xFF, // Return
            0x00, // Return
            0x00, // Return
            0x00, // Return
            0x00, // Return
            0x00, // Return
    };

    // HWINPUT::mcstring a = "Hello World"_mc;
    // hwlib::target::pin_out status = hwlib::target::pin_out(hwlib::target::pins::d13);
    // status.set(true);

    hwlib::target::pin_out clock = hwlib::target::pin_out(hwlib::target::pins::d13);
    clock.set(true);
    hwlib::target::pin_out command = hwlib::target::pin_out(hwlib::target::pins::d4 );
    hwlib::target::pin_in data = hwlib::target::pin_in(hwlib::target::pins::d3);
    data.pullup_disable();

    hwlib::target::pin_in acknolage = hwlib::target::pin_in(hwlib::target::pins::d6);
    acknolage.pullup_disable();
    hwlib::target::pin_out attention = hwlib::target::pin_out(hwlib::target::pins::d7);

    attention.set(true);


    while(true) {
        attention.set(false);
        hwlib::wait_ms(5);
        clock.set(false);
        hwlib::wait_ms(5);
        clock.set(true);
        for(unsigned int i = 0; i < 5; i++) {
            hwlib::cout << "Packet #" << i << hwlib::endl << hwlib::flush;
            hwlib::wait_ms(2);
            uint_fast8_t byte = command_script[i];
            uint_fast8_t output = 0x00;
            for(unsigned int bit_i = 0; bit_i < 8; bit_i++){
                bool b = (byte & (0x1 << bit_i));
                command.set(b);
                // status.set(b);
                hwlib::wait_ms(1);
                clock.set(false);

                hwlib::wait_ms(5);

                clock.set(true);
                data.refresh();
                bool input = data.get();
                hwlib::cout << input;

                output <<= 1;
                output |= input;
            }
            hwlib::cout << hwlib::endl << hwlib::flush;
            hwlib::wait_ms(20);
            attention.set(true);
            hwlib::cout << output << hwlib::endl << hwlib::flush;
            hwlib::wait_ms(200);
        }
        attention.set(true);
    }
    return 0;
}
