#include "all_your_base.h"

#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base) {
    // Validate bases
    if (input_base <= 1 || output_base <= 1) {
        throw std::invalid_argument("Bases must be greater than 1");
    }

    // Validate digit list
    if (digits.empty()) {
        throw std::invalid_argument("Input digit list is empty");
    }
    // Leading zeros are allowed; they do not affect the computed value.
    for (auto d : digits) {
        if (d >= input_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    // Convert input digits to a scalar value (unsigned long long)
    unsigned long long value = 0;
    for (auto d : digits) {
        value = value * input_base + d;
    }

    // Special-case zero
    if (value == 0) {
        return {0};
    }

    // Convert scalar value to the output base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(static_cast<unsigned int>(value % output_base));
        value /= output_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
