#include "all_your_base.h"
#include <stdexcept>
#include <algorithm>
#include <cstdint>

namespace all_your_base {

std::vector<unsigned int> convert(int from_base, const std::vector<unsigned int>& digits, int to_base) {
    // Validate bases
    if (from_base < 2) {
        throw std::invalid_argument("from base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to base must be >= 2");
    }

    // Validate digits
    if (digits.empty()) {
        throw std::invalid_argument("digits must not be empty");
    }
    // No leading zeros allowed unless the number itself is zero
    if (digits.size() > 1 && digits.front() == 0) {
        throw std::invalid_argument("invalid leading zeros");
    }

    std::int64_t value = 0;
    for (unsigned int d : digits) {
        if (d >= static_cast<unsigned int>(from_base)) {
            throw std::invalid_argument("invalid digit in input");
        }
        value = value * from_base + d;
    }

    // Special case zero
    if (value == 0) {
        return {0};
    }

    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(static_cast<unsigned int>(value % to_base));
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
