#include "all_your_base.h"

#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base) {
    // Validate bases
    if (from_base < 2) {
        throw std::invalid_argument("from_base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("to_base must be >= 2");
    }

    // Validate digits
    if (!digits.empty()) {
        for (auto d : digits) {
            if (d >= from_base) {
                throw std::invalid_argument("All digits must be less than from_base");
            }
        }
    }

    // Special case: empty input returns empty output
    if (digits.empty()) {
        return {};
    }

    // Convert input digits to integer value
    unsigned int value = 0;
    for (auto d : digits) {
        value = value * from_base + d;
    }

    // Special case: input is single zero
    if (digits.size() == 1 && digits[0] == 0) {
        return {};
    }

    // Convert integer value to output base
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(value % to_base);
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
