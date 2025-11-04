#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base) {
    // Validate bases
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be >= 2.");
    }

    // Reject empty input list – it is invalid per specification
    if (digits.empty()) {
        throw std::invalid_argument("Input digit sequence is empty.");
    }

    // Reject leading zeros (except when the whole number is zero)
    if (digits.size() > 1 && digits.front() == 0) {
        throw std::invalid_argument("Leading zeros are not allowed.");
    }

    // Special-case: input represents zero (all digits are 0)
    bool has_non_zero = false;
    for (unsigned int d : digits) {
        if (d != 0) {
            has_non_zero = true;
            break;
        }
    }
    if (!has_non_zero) {
        return {0};
    }

    // Validate digits and compute the value in an unsigned long long
    unsigned long long value = 0;
    for (unsigned int d : digits) {
        if (d >= input_base) {
            throw std::invalid_argument("Digit out of range for input base.");
        }
        value = value * input_base + d;
    }

    // Convert the value to the output base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(static_cast<unsigned int>(value % output_base));
        value /= output_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
