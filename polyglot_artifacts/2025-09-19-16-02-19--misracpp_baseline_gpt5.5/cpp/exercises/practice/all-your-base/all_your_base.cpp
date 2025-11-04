#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int in_base, const std::vector<unsigned int>& digits, unsigned int out_base) {
    if (in_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (out_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Trim leading zeros
    auto first_non_zero = std::find_if(digits.begin(), digits.end(),
                                       [](unsigned int d) { return d != 0U; });

    // If all digits are zero or the list is empty, the value is zero.
    if (first_non_zero == digits.end()) {
        return {};
    }

    // Validate digits
    for (auto it = first_non_zero; it != digits.end(); ++it) {
        if (*it >= in_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }

    // Accumulate the value in base 'out_base' using multiply-add to avoid overflow.
    // We store the accumulator in little-endian (least significant digit first).
    std::vector<unsigned int> acc;  // base 'out_base', LSB at index 0

    for (auto it = first_non_zero; it != digits.end(); ++it) {
        const unsigned int d = *it;

        // acc = acc * in_base
        unsigned long long carry = 0ULL;
        for (std::size_t i = 0; i < acc.size(); ++i) {
            unsigned long long v = static_cast<unsigned long long>(acc[i]) * static_cast<unsigned long long>(in_base) + carry;
            acc[i] = static_cast<unsigned int>(v % out_base);
            carry = v / out_base;
        }
        while (carry > 0ULL) {
            acc.push_back(static_cast<unsigned int>(carry % out_base));
            carry /= out_base;
        }

        // acc = acc + d
        carry = static_cast<unsigned long long>(d);
        for (std::size_t i = 0; i < acc.size(); ++i) {
            unsigned long long v = static_cast<unsigned long long>(acc[i]) + carry;
            acc[i] = static_cast<unsigned int>(v % out_base);
            carry = v / out_base;
        }
        while (carry > 0ULL) {
            acc.push_back(static_cast<unsigned int>(carry % out_base));
            carry /= out_base;
        }
    }

    if (acc.empty()) {
        return {};
    }

    // Convert to big-endian (most significant digit first)
    std::vector<unsigned int> out(acc.rbegin(), acc.rend());
    return out;
}

}  // namespace all_your_base
