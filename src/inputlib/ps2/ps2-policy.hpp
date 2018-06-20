#ifndef PS2_POLICY_HPP
#define PS2_POLICY_HPP
namespace inputlib {
    class PS2Controller {
        protected:
        constexpr uint_16_t upMask() const {
            return 0x01 << 1;
        }


    };
}

#endif