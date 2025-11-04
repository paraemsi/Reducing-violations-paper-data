#include "all_your_base.h"

#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& in_digits,
                                  unsigned int to_base) {
    // Validate bases
    if (from_base < 2 || to_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digits
    for (auto d : in_digits) {
        if (d >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    // Special cases and additional validation
    if (in_digits.empty()) {
        return {};
    }

    bool all_zero = std::all_of(in_digits.begin(), in_digits.end(),
                                [](unsigned int d) { return d == 0; });


    if (all_zero) {
        return {};
    }

    // Convert input digits to an integer value
    unsigned long long value = 0;
    for (auto d : in_digits) {
        value = value * from_base + d;
    }

    // Convert value to output digits
    std::vector<unsigned int> out_digits;
    while (value > 0) {
        out_digits.push_back(static_cast<unsigned int>(value % to_base));
        value /= to_base;
    }
    std::reverse(out_digits.begin(), out_digits.end());

    return out_digits;
}

}  // namespace all_your_base
