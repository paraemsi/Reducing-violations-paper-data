#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

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

    // Empty input yields empty output
    if (digits.empty()) {
        return {};
    }

    // Validate digits
    for (auto d : digits) {
        if (d >= input_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }

    // Trim leading zeros
    std::size_t first_non_zero = 0;
    while (first_non_zero < digits.size() && digits[first_non_zero] == 0) {
        ++first_non_zero;
    }

    // If the number is zero
    if (first_non_zero == digits.size()) {
        return {0u};
    }

    // Work on a trimmed copy
    std::vector<unsigned int> in(digits.begin() + first_non_zero, digits.end());
    std::vector<unsigned int> out;
    out.reserve(in.size()); // rough upper bound

    // Repeated division algorithm to avoid large integer overflow
    while (!in.empty()) {
        std::vector<unsigned int> next;
        next.reserve(in.size());
        unsigned int carry = 0;

        for (auto d : in) {
            // value fits in 64-bit for typical exercise constraints
            unsigned long long value = static_cast<unsigned long long>(carry) * static_cast<unsigned long long>(input_base) + static_cast<unsigned long long>(d);
            unsigned int q = static_cast<unsigned int>(value / static_cast<unsigned long long>(output_base));
            carry = static_cast<unsigned int>(value % static_cast<unsigned long long>(output_base));
            if (!next.empty() || q != 0) {
                next.push_back(q);
            }
        }

        out.push_back(carry);
        in.swap(next);
    }

    std::reverse(out.begin(), out.end());
    return out;
}

}  // namespace all_your_base
