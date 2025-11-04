#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int in_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int out_base) {
    if (in_base < 2 || out_base < 2) {
        throw std::invalid_argument("base must be >= 2");
    }

    if (digits.empty()) {
        return {};
    }

    // Validate digits and find first non-zero (to trim leading zeros)
    for (auto d : digits) {
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    auto first_non_zero = std::find_if(digits.begin(), digits.end(),
                                       [](unsigned int d) { return d != 0; });

    // If the number is zero, return {0}
    if (first_non_zero == digits.end()) {
        return {0};
    }

    // Represent the accumulating result in the output base directly to avoid overflow:
    // For each input digit d: result = result * in_base + d
    std::vector<unsigned int> result{0};

    for (auto it = first_non_zero; it != digits.end(); ++it) {
        unsigned int d = *it;

        // result *= in_base
        unsigned int carry_mul = 0;
        for (int i = static_cast<int>(result.size()) - 1; i >= 0; --i) {
            unsigned long long value =
                static_cast<unsigned long long>(result[i]) * in_base + carry_mul;
            result[i] = static_cast<unsigned int>(value % out_base);
            carry_mul = static_cast<unsigned int>(value / out_base);
        }
        while (carry_mul > 0) {
            result.insert(result.begin(), carry_mul % out_base);
            carry_mul /= out_base;
        }

        // result += d
        unsigned int carry_add = d;
        for (int i = static_cast<int>(result.size()) - 1; i >= 0; --i) {
            unsigned long long value =
                static_cast<unsigned long long>(result[i]) + carry_add;
            result[i] = static_cast<unsigned int>(value % out_base);
            carry_add = static_cast<unsigned int>(value / out_base);
        }
        while (carry_add > 0) {
            result.insert(result.begin(), carry_add % out_base);
            carry_add /= out_base;
        }
    }

    return result;
}

}  // namespace all_your_base
