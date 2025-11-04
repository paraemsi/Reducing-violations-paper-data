#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(int input_base, const std::vector<unsigned int>& digits, int output_base) {
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("base must be >= 2");
    }
    if (digits.empty()) {
        return {};
    }

    // Skip leading zeros
    std::size_t start = 0;
    while (start < digits.size() && digits[start] == 0) {
        ++start;
    }
    if (start == digits.size()) {
        return {0};
    }

    // Validate digits
    for (std::size_t i = start; i < digits.size(); ++i) {
        if (digits[i] >= static_cast<unsigned int>(input_base)) {
            throw std::invalid_argument("invalid digit");
        }
    }

    // Prepare trimmed source digits
    std::vector<unsigned int> source(digits.begin() + start, digits.end());

    // Repeated division algorithm to avoid overflow
    std::vector<unsigned int> out;
    while (!source.empty()) {
        unsigned long long carry = 0ULL;
        std::vector<unsigned int> quotient;
        quotient.reserve(source.size());

        for (unsigned int d : source) {
            unsigned long long value = carry * static_cast<unsigned long long>(input_base) + d;
            unsigned int q_digit = static_cast<unsigned int>(value / static_cast<unsigned long long>(output_base));
            carry = value % static_cast<unsigned long long>(output_base);

            if (!quotient.empty() || q_digit != 0U) {
                quotient.push_back(q_digit);
            }
        }

        out.push_back(static_cast<unsigned int>(carry));
        source.swap(quotient);
    }

    std::reverse(out.begin(), out.end());
    if (out.empty()) {
        out.push_back(0);
    }
    return out;
}

}  // namespace all_your_base
