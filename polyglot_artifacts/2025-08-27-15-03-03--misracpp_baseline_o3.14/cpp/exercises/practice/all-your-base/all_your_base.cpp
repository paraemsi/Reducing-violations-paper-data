#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base) {
    // Validate bases
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Validate digits
    if (digits.empty()) {
        throw std::invalid_argument("digits vector must not be empty");
    }
    for (unsigned int d : digits) {
        if (d >= input_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    // Convert to an integer value
    unsigned long long value = 0;
    for (unsigned int d : digits) {
        value = value * input_base + d;
    }

    // Special-case: the value zero
    if (value == 0) {
        return {0};
    }

    // Convert integer value to the output base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(static_cast<unsigned int>(value % output_base));
        value /= output_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
