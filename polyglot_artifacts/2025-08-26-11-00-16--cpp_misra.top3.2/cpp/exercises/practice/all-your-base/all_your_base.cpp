#include "all_your_base.h"
#include <stdexcept>

namespace all_your_base {

Digits convert(std::uint32_t from_base, const Digits& in_digits, std::uint32_t to_base)
{
    // Validate bases
    if((from_base < static_cast<std::uint32_t>(2)) || (to_base < static_cast<std::uint32_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate input digits
    if(in_digits.empty()) {
        return Digits{};
    }
    bool all_zero = true;
    for(const Digit d : in_digits) {
        if(d >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        if(d != static_cast<Digit>(0)) {
            all_zero = false;
        }
    }
    if(all_zero) {
        return Digits{};
    }

    // Convert input digits to integer value
    std::uint64_t value = 0;
    for(std::size_t i = 0U; i < in_digits.size(); ++i) {
        value = (value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(in_digits[i]);
    }

    // Convert integer value to output base
    Digits out_digits;
    while(value > static_cast<std::uint64_t>(0)) {
        out_digits.insert(out_digits.begin(), static_cast<Digit>(value % static_cast<std::uint64_t>(to_base)));
        value = value / static_cast<std::uint64_t>(to_base);
    }

    return out_digits;
}

}  // namespace all_your_base
