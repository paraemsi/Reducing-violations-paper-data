#include "all_your_base.h"

#include <stdexcept>
#include <algorithm>
#include <limits>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base) {
    if (from_base < 2) {
        throw std::invalid_argument("from_base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to_base must be >= 2");
    }
    // Check for invalid digits
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("all digits must be < from_base");
        }
    }
    // Remove leading zeros
    auto first_nonzero = std::find_if(digits.begin(), digits.end(), [](unsigned int d) { return d != 0; });
    std::vector<unsigned int> trimmed_digits(first_nonzero, digits.end());
    if (trimmed_digits.empty()) {
        return {0};
    }

    // Convert input digits to an integer value
    unsigned int value = 0;
    for (auto d : trimmed_digits) {
        // Check for overflow
        if (value > (std::numeric_limits<unsigned int>::max() - d) / from_base) {
            throw std::overflow_error("number too large to convert");
        }
        value = value * from_base + d;
    }

    // Convert integer value to output base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(value % to_base);
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
