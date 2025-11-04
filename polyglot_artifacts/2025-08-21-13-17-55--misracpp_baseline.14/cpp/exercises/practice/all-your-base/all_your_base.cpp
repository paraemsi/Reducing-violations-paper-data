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
        // Only throw for leading zeros if there is more than one digit and not all are zero
        bool all_zeros = std::all_of(digits.begin(), digits.end(), [](unsigned int d){ return d == 0; });
        bool leading_zero = digits[0] == 0 && digits.size() > 1 && !all_zeros;
        if (leading_zero) {
            throw std::invalid_argument("digits may not contain leading zeros");
        }
        for (auto d : digits) {
            if (d >= from_base) {
                throw std::invalid_argument("all digits must be < from_base");
            }
        }
    }

    // Special case: empty input
    if (digits.empty()) {
        return std::vector<unsigned int>{};
    }

    // Special case: all zeros
    bool all_zeros = std::all_of(digits.begin(), digits.end(), [](unsigned int d){ return d == 0; });
    if (all_zeros) {
        return std::vector<unsigned int>{0};
    }

    // Convert input digits to an integer value
    unsigned long long value = 0;
    for (auto d : digits) {
        value = value * from_base + d;
    }

    // Convert integer value to output base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(static_cast<unsigned int>(value % to_base));
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
