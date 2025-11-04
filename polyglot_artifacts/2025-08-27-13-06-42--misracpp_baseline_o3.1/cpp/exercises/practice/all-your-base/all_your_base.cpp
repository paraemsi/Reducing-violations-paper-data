#include "all_your_base.h"
#include <stdexcept>
#include <algorithm>
#include <cstdint>
#include <limits>

namespace all_your_base {

std::vector<unsigned int> convert(int from_base, const std::vector<unsigned int>& digits, int to_base) {
    // Validate bases
    if (from_base < 2) {
        throw std::invalid_argument("from_base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to_base must be >= 2");
    }

    // Validate digits
    if (digits.empty()) {
        throw std::invalid_argument("digits must not be empty");
    }
    bool is_zero = true;
    for (unsigned int d : digits) {
        if (d >= static_cast<unsigned int>(from_base)) {
            throw std::invalid_argument("digits contain invalid value");
        }
        if (d != 0) {
            is_zero = false;
        }
    }

    // All digits were zero -> the represented number is zero.
    if (is_zero) {
        return {0};
    }

    // Convert input digits to a base-10 value.
    std::uint64_t value = 0;
    for (unsigned int d : digits) {
        if (value > (std::numeric_limits<std::uint64_t>::max() - d) / static_cast<std::uint64_t>(from_base)) {
            throw std::overflow_error("value too large to represent");
        }
        value = value * static_cast<std::uint64_t>(from_base) + static_cast<std::uint64_t>(d);
    }

    // Convert base-10 value to target base.
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(static_cast<unsigned int>(value % to_base));
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
