#include "all_your_base.h"

#include <algorithm>
#include <cstddef>

namespace all_your_base {

std::vector<unsigned int> convert(
    unsigned int from_base,
    const std::vector<unsigned int>& digits,
    unsigned int to_base
) {
    // Validate bases
    if (from_base < 2) {
        throw std::invalid_argument("from_base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to_base must be >= 2");
    }

    // Validate digits
    bool leading = true;
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("digit out of range for from_base");
        }
        if (leading && d == 0) {
            continue;
        }
        leading = false;
    }

    // Remove leading zeros
    auto it = std::find_if(digits.begin(), digits.end(), [](unsigned int d) { return d != 0; });
    std::vector<unsigned int> clean_digits(it, digits.end());

    // Special case: input is zero or empty
    if (clean_digits.empty()) {
        return {};
    }

    // Convert input digits to an integer value
    unsigned long long value = 0;
    for (auto d : clean_digits) {
        value = value * from_base + d;
    }

    // Special case: if the value is zero, return empty vector
    if (value == 0) {
        return {};
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
