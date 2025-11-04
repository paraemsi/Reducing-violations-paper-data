#include "all_your_base.h"

#include <vector>
#include <stdexcept>
#include <algorithm>

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
    std::vector<unsigned int> clean_digits(first_nonzero, digits.end());
    if (clean_digits.empty()) {
        // If input is empty or all zeros, return empty vector (not {0})
        return {};
    }

    // Convert input digits to an integer value
    unsigned long long value = 0;
    for (auto d : clean_digits) {
        value = value * from_base + d;
    }

    // Special case: if value is zero, return empty vector
    if (value == 0) {
        return {};
    }

    // Convert integer value to output base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.insert(result.begin(), value % to_base);
        value /= to_base;
    }
    return result;
}

}  // namespace all_your_base
