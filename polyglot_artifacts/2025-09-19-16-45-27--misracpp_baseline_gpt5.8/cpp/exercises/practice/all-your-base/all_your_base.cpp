#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int in_base,
                                  const std::vector<unsigned int>& in_digits,
                                  unsigned int out_base) {
    if (in_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (out_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Skip leading zeros
    auto first_non_zero = std::find_if(in_digits.begin(), in_digits.end(),
                                       [](unsigned int d) { return d != 0u; });

    // If all digits are zero (or input is empty), the value is zero.
    if (first_non_zero == in_digits.end()) {
        return {};
    }

    // Validate digits
    for (auto it = first_non_zero; it != in_digits.end(); ++it) {
        if (*it >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    // Result stored little-endian in out_base for easy arithmetic.
    std::vector<unsigned int> result_le;

    // Process each input digit: result = result * in_base + digit
    for (auto it = first_non_zero; it != in_digits.end(); ++it) {
        unsigned int d = *it;

        // Multiply current result by in_base and add d, all in out_base representation.
        unsigned long long carry = d;
        for (std::size_t i = 0; i < result_le.size(); ++i) {
            unsigned long long value =
                static_cast<unsigned long long>(result_le[i]) * in_base + carry;
            result_le[i] = static_cast<unsigned int>(value % out_base);
            carry = value / out_base;
        }
        while (carry > 0) {
            result_le.push_back(static_cast<unsigned int>(carry % out_base));
            carry /= out_base;
        }
    }

    if (result_le.empty()) {
        return {};
    }

    // Convert to big-endian for output.
    std::vector<unsigned int> result_be(result_le.rbegin(), result_le.rend());
    return result_be;
}

}  // namespace all_your_base
