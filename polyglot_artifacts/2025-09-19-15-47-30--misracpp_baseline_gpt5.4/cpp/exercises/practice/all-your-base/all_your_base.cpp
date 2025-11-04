#include "all_your_base.h"

#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int in_base, const std::vector<unsigned int>& digits, unsigned int out_base) {
    if (in_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (out_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    if (digits.empty()) {
        // Empty input yields empty output per common convention for this exercise.
        return {};
    }

    // Validate digits
    for (auto d : digits) {
        if (d >= in_base) {
            throw std::invalid_argument("all digits must be < input base");
        }
    }

    // Skip leading zeros
    std::size_t first_nonzero = 0;
    while (first_nonzero < digits.size() && digits[first_nonzero] == 0) {
        ++first_nonzero;
    }

    // If value is zero, return an empty vector
    if (first_nonzero == digits.size()) {
        return {};
    }

    // Working copy of the number without leading zeros (in base in_base)
    std::vector<unsigned int> number(digits.begin() + static_cast<std::ptrdiff_t>(first_nonzero), digits.end());

    // Repeated division algorithm: divide by out_base, collect remainders
    std::vector<unsigned int> out_reversed;
    while (!number.empty()) {
        std::vector<unsigned int> quotient;
        quotient.reserve(number.size());
        unsigned long long remainder = 0ULL;

        for (auto d : number) {
            unsigned long long value = remainder * static_cast<unsigned long long>(in_base) + static_cast<unsigned long long>(d);
            unsigned int qdigit = static_cast<unsigned int>(value / out_base);
            remainder = static_cast<unsigned int>(value % out_base);
            if (!quotient.empty() || qdigit != 0U) {
                quotient.push_back(qdigit);
            }
        }

        out_reversed.push_back(static_cast<unsigned int>(remainder));
        number.swap(quotient);
    }

    std::reverse(out_reversed.begin(), out_reversed.end());
    return out_reversed;
}

}  // namespace all_your_base
