#include "all_your_base.h"

#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base, const std::vector<unsigned int>& digits, unsigned int to_base) {
    // Validate bases
    if (from_base < 2) {
        throw std::invalid_argument("from_base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to_base must be >= 2");
    }

    // Validate digits
    if (!digits.empty()) {
        // Only check for leading zeros if more than one digit
        if (digits.size() > 1 && digits[0] == 0) {
            throw std::invalid_argument("digits may not contain leading zeros");
        }
        for (auto d : digits) {
            if (d >= from_base) {
                throw std::invalid_argument("all digits must be < from_base");
            }
        }
    }

    // Special case: empty input means empty output
    if (digits.empty()) {
        return {};
    }

    // Special case: all digits are zero (possibly multiple zeros)
    bool all_zeros = std::all_of(digits.begin(), digits.end(), [](unsigned int d){ return d == 0; });
    if (all_zeros) {
        return {};
    }

    // Convert input digits to base 10 integer
    unsigned long long value = 0;
    for (auto d : digits) {
        value = value * from_base + d;
    }

    // Convert base 10 integer to output base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(static_cast<unsigned int>(value % to_base));
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
