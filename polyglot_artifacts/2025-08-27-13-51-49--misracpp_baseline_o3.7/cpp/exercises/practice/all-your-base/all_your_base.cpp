#include "all_your_base.h"
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base) {
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    // An empty digit sequence represents zero; handle it naturally below.

    // Skip leading zeros
    std::size_t idx = 0;
    while (idx < digits.size() && digits[idx] == 0) {
        ++idx;
    }
    if (idx == digits.size()) {
        return {0};
    }

    unsigned long long value = 0;
    for (; idx < digits.size(); ++idx) {
        unsigned int d = digits[idx];
        if (d >= input_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        value = value * input_base + d;
    }

    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(static_cast<unsigned int>(value % output_base));
        value /= output_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
