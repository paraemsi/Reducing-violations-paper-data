#include "all_your_base.h"
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base) {
    // Validate bases
    if (from_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Validate digits
    if (digits.empty()) {
        throw std::invalid_argument("digits must not be empty");
    }

    bool all_zero = true;
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("all digits must be < input base");
        }
        if (d != 0) {
            all_zero = false;
        }
    }

    if (all_zero) {
        return {0};
    }

    // Use repeated division to perform the base conversion.
    // Treat the input as a big-integer in `from_base` and repeatedly divide it
    // by `to_base`, collecting the remainders (least-significant digits first).
    std::vector<unsigned int> result;              // Output digits in LSB-first order
    std::vector<unsigned int> current = digits;    // Remaining value in from_base

    while (!current.empty()) {
        std::vector<unsigned int> next;            // Quotient of current / to_base
        unsigned long long remainder = 0;

        for (unsigned int d : current) {
            unsigned long long value = remainder * from_base + d;
            unsigned int quotient_digit =
                static_cast<unsigned int>(value / to_base);
            remainder = value % to_base;

            // Avoid leading zeros in the quotient
            if (!next.empty() || quotient_digit != 0) {
                next.push_back(quotient_digit);
            }
        }

        result.push_back(static_cast<unsigned int>(remainder));
        current.swap(next);                        // Continue with the quotient
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
