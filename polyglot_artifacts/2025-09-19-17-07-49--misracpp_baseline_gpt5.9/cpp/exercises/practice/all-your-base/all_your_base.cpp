#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(int in_base, const std::vector<unsigned int>& digits, int out_base) {
    if (in_base < 2 || out_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digits
    for (auto d : digits) {
        if (d >= static_cast<unsigned int>(in_base)) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    // Strip leading zeros
    std::size_t first_non_zero = 0;
    while (first_non_zero < digits.size() && digits[first_non_zero] == 0) {
        ++first_non_zero;
    }

    // If the number is zero or no digits, return an empty representation
    if (first_non_zero == digits.size()) {
        return {};
    }

    // Work on a copy without leading zeros
    std::vector<unsigned int> source(digits.begin() + static_cast<std::ptrdiff_t>(first_non_zero), digits.end());
    std::vector<unsigned int> result;

    // Repeated division algorithm to avoid big integer overflow
    while (!source.empty()) {
        std::vector<unsigned int> quotient;
        unsigned long long carry = 0ULL;

        for (auto d : source) {
            unsigned long long acc = carry * static_cast<unsigned long long>(in_base) + d;
            unsigned int q_digit = static_cast<unsigned int>(acc / static_cast<unsigned long long>(out_base));
            carry = acc % static_cast<unsigned long long>(out_base);

            if (!quotient.empty() || q_digit != 0u) {
                quotient.push_back(q_digit);
            }
        }

        result.push_back(static_cast<unsigned int>(carry));
        source.swap(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
