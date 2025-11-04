#include "all_your_base.h"

#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(
    unsigned int from_base,
    const std::vector<unsigned int>& digits,
    unsigned int to_base)
{
    if (from_base < 2) {
        throw std::invalid_argument("from_base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to_base must be >= 2");
    }
    if (digits.empty()) {
        return {};
    }
    // Check for invalid digits
    bool all_zero = true;
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("digit out of range for from_base");
        }
        if (d != 0) {
            all_zero = false;
        }
    }
    if (all_zero) {
        return {};
    }

    // Convert input digits to an integer value
    unsigned long long value = 0;
    for (auto d : digits) {
        value = value * from_base + d;
    }

    // Convert integer value to to_base digits
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(value % to_base);
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
