#include "all_your_base.h"
#include <algorithm>

namespace all_your_base {

std::vector<int> convert(int from_base,
                         const std::vector<int>& digits,
                         int to_base) {
    // Validate bases.
    if (from_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Validate digits.
    if (digits.empty()) {
        throw std::invalid_argument("no digits provided");
    }
    for (unsigned int d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    // Remove leading zeros; if all digits are zero return {0}.
    auto first_non_zero = std::find_if(digits.begin(), digits.end(),
                                       [](int d) { return d != 0; });
    if (first_non_zero == digits.end()) {
        return {0u};
    }

    // Working copy of the number in the source base.
    std::vector<int> value(first_non_zero, digits.end());

    std::vector<int> result;      // Digits in the target base (LSB first).
    while (!value.empty()) {
        std::vector<int> quotient;
        int remainder = 0;

        for (int d : value) {
            long long accumulator =
                static_cast<long long>(remainder) * from_base + d;
            int q_digit  = static_cast<int>(accumulator / to_base);
            remainder    = static_cast<int>(accumulator % to_base);

            if (!quotient.empty() || q_digit != 0u) {
                quotient.push_back(q_digit);
            }
        }

        result.push_back(remainder);
        value.swap(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
