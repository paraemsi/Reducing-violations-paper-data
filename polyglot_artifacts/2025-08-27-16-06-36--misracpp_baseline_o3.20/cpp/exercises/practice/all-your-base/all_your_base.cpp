#include "all_your_base.h"
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(int input_base,
                                  const std::vector<unsigned int>& digits,
                                  int output_base) {
    // Validate bases
    if (input_base <= 1) {
        throw std::invalid_argument("input base must be > 1");
    }
    if (output_base <= 1) {
        throw std::invalid_argument("output base must be > 1");
    }

    // Handle empty input as zero
    if (digits.empty()) {
        return {0};
    }

    // Validate digits and compute value in 64-bit integer
    long long value = 0;
    for (unsigned int d : digits) {
        if (d >= static_cast<unsigned int>(input_base)) {
            throw std::invalid_argument("invalid digit in input");
        }
        value = value * input_base + d;
    }

    // Special case: value is zero
    if (value == 0) {
        return {0};
    }

    // Convert to output base
    std::vector<unsigned int> out_digits;
    while (value > 0) {
        out_digits.push_back(static_cast<unsigned int>(value % output_base));
        value /= output_base;
    }
    std::reverse(out_digits.begin(), out_digits.end());
    return out_digits;
}

}  // namespace all_your_base
