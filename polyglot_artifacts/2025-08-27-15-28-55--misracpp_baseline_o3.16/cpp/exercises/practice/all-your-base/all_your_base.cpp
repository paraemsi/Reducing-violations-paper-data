#include "all_your_base.h"
#include <algorithm>  // for std::reverse

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base) {
    // Validate bases
    if (from_base < 2 || to_base < 2) {
        throw std::invalid_argument("Bases must be >= 2.");
    }

    // Remove leading zeros and handle all-zero input
    std::vector<unsigned int> current;
    auto first_non_zero = std::find_if(digits.begin(), digits.end(),
                                       [](unsigned int d) { return d != 0; });
    if (first_non_zero == digits.end()) {
        return {0};
    }
    current.assign(first_non_zero, digits.end());

    // Validate digits are within range of from_base
    for (unsigned int d : current) {
        if (d >= from_base) {
            throw std::invalid_argument("Digits out of range for input base.");
        }
    }

    // Repeated-division algorithm: convert without using big built-in integers
    std::vector<unsigned int> result;  // will store digits in reverse order
    while (!current.empty()) {
        std::vector<unsigned int> next;
        unsigned long long remainder = 0;

        for (unsigned int d : current) {
            unsigned long long acc = remainder * from_base + d;
            unsigned int q_digit   = static_cast<unsigned int>(acc / to_base);
            remainder              = acc % to_base;

            if (!next.empty() || q_digit != 0) {
                next.push_back(q_digit);  // skip leading zeros in quotient
            }
        }

        result.push_back(static_cast<unsigned int>(remainder));
        current.swap(next);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
