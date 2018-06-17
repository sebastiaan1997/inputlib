#include "wrap-hwlib.hpp"

#include "pin_log_decorator.hpp"
struct pinset {
    hwlib::target::pin_in data;
    hwlib::target::pin_out command;
    hwlib::target::pin_out attention;
    hwlib::target::pin_out clock;
    hwlib::target::pin_in  acknoledge;
};

typedef hwlib::target::pins duepin ;

int main() {
// Wait for the serial connection to connect
    hwlib::wait_ms(500);
    hwlib::target::pin_adc analog_data(hwlib::target::ad_pins::a0);
    pinset p = {
        hwlib::target::pin_in(duepin::d13),
        hwlib::target::pin_out(duepin::d4),
        hwlib::target::pin_out(duepin::d5),
        hwlib::target::pin_out(duepin::d6),
        hwlib::target::pin_in(duepin::d7)
    };

    p.clock.set(0);
    p.command.set(0);
    p.attention.set(1);
    p.data.pullup_enable();
    p.acknoledge.pullup_enable();

    hwlib::wait_ms(500);
    std::array<uint_fast8_t, 5> commands = {
        0x01,
        0x42,
        0x00,
        0x00,
        0x00
    };
    while(true) {
        hwlib::cout << "=== start transaction ===" << hwlib::endl << hwlib::flush;
        for(auto command: commands) {
            p.attention.set(0);
            uint_fast8_t data = 0x00;
            uint_fast32_t analog_value;
            hwlib::cout << "==== Packet ====" << hwlib::endl;
            for(unsigned int i = 0; i < 8; i++) {
                bool value = command & 0x01;
                command <<= 1;
                hwlib::wait_ms(1);
                p.command.set(value);
                hwlib::wait_ms(2);
                p.clock.set(1);
                hwlib::wait_ms(10);
                bool output = p.data.get();
                analog_value = analog_data.get();
                p.clock.set(0);
                data <<= 1;
                data |= output;
                hwlib::cout << output;
            };
            
            hwlib::cout << hwlib::endl << "Dec => " << data << hwlib::endl;
            hwlib::cout << "Analog => " << analog_value << hwlib::endl;
        }
        hwlib::cout << "=== end transaction ===" << hwlib::endl << hwlib::flush;
    }

    return 0;
}
