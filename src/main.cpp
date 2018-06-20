#include "wrap-hwlib.hpp"

#include "pin_log_decorator.hpp"
#include "inputlib/inputlib.hpp"

struct pinset {
    hwlib::target::pin_in data;
    hwlib::target::pin_out command;
    hwlib::target::pin_out attention;
    hwlib::target::pin_out clock;
    hwlib::target::pin_in  acknoledge;
};

typedef hwlib::target::pins duepin;
// Ps2Bus(hwlib::pin_out& sclk, hwlib::pin_in& miso, hwlib::pin_out& mosi, hwlib::pin_in& acknolage)
int main() {
    // Kill the watchdoggo 
    WDT->WDT_MR = WDT_MR_WDDIS;
    pinset p = {
        hwlib::target::pin_in(duepin::d3),
        hwlib::target::pin_out(duepin::d4),
        hwlib::target::pin_out(duepin::d5),
        hwlib::target::pin_out(duepin::d6),
        hwlib::target::pin_in(duepin::d7)
    };
        
    std::array<uint8_t, 5> data = {
        0x00,
        0x00,
        0x00,
        0x00,
        0x00
    };

    p.attention.set(1);
    p.attention.flush();
    hwlib::wait_ms(500);

    inputlib::Ps2Bus bus(p.clock, p.data, p.command, p.acknoledge);
    while(true){        
        p.attention.set(0);
        p.attention.flush();
        hwlib::wait_ms(5);
        bus.write_and_read(p.attention, commands.size(),  commands.data(), data.data());
        p.attention.set(1);
        p.attention.flush();
        hwlib::wait_ms(5);
        for(unsigned int i = 0; i < data.size(); i++) {
            hwlib::cout << int(commands[i]) << " => " << int(data[i]) << hwlib::endl << hwlib::flush;
        }
    }

// Wait for the serial connection to connect
    /*hwlib::wait_ms(500);
    hwlib::target::pin_adc analog_data(hwlib::target::ad_pins::a0);
    

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
        for(unsigned int i = 0; i < commands.size(); i++) {
            p.attention.set(0);
            p.attention.flush();
            hwlib::wait_ms(4);
            uint_fast8_t data = 0x00;
            uint_fast32_t analog_value;
            hwlib::cout << "==== Packet ====" << hwlib::endl;
            hwlib::cout << "Command => " << commands[i] << hwlib::endl;
            
            hwlib::wait_ms(1);
            hwlib::cout << "Bin(Command) => ";

            auto command = commands[i];
            for(unsigned int i = 0; i < 8; i++) {
                bool value = (command >> i) & 1;
                hwlib::cout << value;
                // command <<= 1;
                hwlib::wait_ms(1);
                p.command.set(value);
                p.command.flush();
                hwlib::wait_ms(2);
                p.clock.set(1);
                hwlib::wait_ms(10);
                bool output = p.data.get();
                analog_value = analog_data.get();
                p.clock.set(0);
                data <<= 1;
                data |= output;
                hwlib::cout << output;
                hwlib::wait_ms(4);
            };
            hwlib::cout << hwlib::endl << "Dec => " << data << hwlib::endl;
            hwlib::cout << "Analog => " << analog_value << hwlib::endl;
        }
        hwlib::cout << "=== end transaction ===" << hwlib::endl << hwlib::flush;
        p.attention.set(1);
    }*/

    return 0;
}
