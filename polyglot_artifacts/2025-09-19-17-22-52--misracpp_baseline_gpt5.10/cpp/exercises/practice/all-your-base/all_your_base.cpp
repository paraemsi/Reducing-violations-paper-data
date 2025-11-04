#include "all_your_base.h"

#include <cstddef>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base) {
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Trim leading zeros
    std::size_t start = 0;
    while (start < digits.size() && digits[start] == 0) {
        ++start;
    }

    // Empty or all-zero input represents zero -> empty output
    if (digits.empty() || start == digits.size()) {
        return {};
    }

    // Validate digits
    for (std::size_t i = start; i < digits.size(); ++i) {
        if (digits[i] >= input_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    // Work on a trimmed copy (no leading zeros)
    std::vector<unsigned int> src(digits.begin() + static_cast<std::ptrdiff_t>(start), digits.end());
    std::vector<unsigned int> out_reversed;
    out_reversed.reserve(src.size());

    // Repeated division algorithm to avoid big integer overflow
    while (!src.empty()) {
        std::vector<unsigned int> quotient;
        quotient.reserve(src.size());

        unsigned long long remainder = 0ULL;
        for (unsigned int d : src) {
            unsigned long long acc = remainder * static_cast<unsigned long long>(input_base) + d;
            unsigned int q_digit = static_cast<unsigned int>(acc / output_base);
            remainder = acc % output_base;

            if (!quotient.empty() || q_digit != 0U) {
                quotient.push_back(q_digit);
            }
        }

        out_reversed.push_back(static_cast<unsigned int>(remainder));
        src.swap(quotient);
    }

    // Reverse to get the correct order
    return std::vector<unsigned int>(out_reversed.rbegin(), out_reversed.rend());
}

}  // namespace all_your_base
