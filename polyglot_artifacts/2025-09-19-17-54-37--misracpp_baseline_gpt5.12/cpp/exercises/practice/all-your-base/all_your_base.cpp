#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(const std::vector<unsigned int>& digits,
                                  int input_base,
                                  int output_base) {
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Strip leading zeros
    auto it = digits.begin();
    while (it != digits.end() && *it == 0) {
        ++it;
    }

    if (it == digits.end()) {
        return {0};
    }

    // Validate digits
    for (auto jt = it; jt != digits.end(); ++jt) {
        if (*jt >= input_base) {
            throw std::invalid_argument("invalid digit for input base");
        }
    }

    // Accumulator in output_base, little-endian (least significant digit first)
    std::vector<unsigned int> acc{0};

    for (; it != digits.end(); ++it) {
        // Multiply acc by input_base
        unsigned long long carry = 0;
        for (auto& d : acc) {
            unsigned long long v = static_cast<unsigned long long>(d) * input_base + carry;
            d = static_cast<unsigned int>(v % output_base);
            carry = static_cast<unsigned int>(v / output_base);
        }
        while (carry != 0) {
            acc.push_back(static_cast<unsigned int>(carry % output_base));
            carry /= output_base;
        }

        // Add current digit
        carry = *it;
        for (size_t i = 0; i < acc.size() && carry != 0; ++i) {
            unsigned long long v = static_cast<unsigned long long>(acc[i]) + carry;
            acc[i] = static_cast<unsigned int>(v % output_base);
            carry = static_cast<unsigned int>(v / output_base);
        }
        while (carry != 0) {
            acc.push_back(static_cast<unsigned int>(carry % output_base));
            carry /= output_base;
        }
    }

    // Remove leading zeros (most significant), ensure at least one digit remains
    while (acc.size() > 1 && acc.back() == 0) {
        acc.pop_back();
    }

    std::reverse(acc.begin(), acc.end());
    return acc;
}

}  // namespace all_your_base
