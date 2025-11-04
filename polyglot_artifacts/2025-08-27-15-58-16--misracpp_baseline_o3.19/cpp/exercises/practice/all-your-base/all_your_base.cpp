#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base) {
    // Validate bases
    if (from_base <= 1 || to_base <= 1) {
        throw std::invalid_argument("Bases must be greater than 1.");
    }

    // Validate digits
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("Digit out of range for input base.");
        }
    }

    // Special-case: empty input or value zero
    bool all_zero = digits.empty();
    if (!all_zero) {
        all_zero = std::all_of(digits.begin(), digits.end(),
                               [](unsigned int d) { return d == 0; });
    }
    if (all_zero) {
        return {0};
    }

    // Make a working copy of the input number (big-endian).
    std::vector<unsigned int> source = digits;
    std::vector<unsigned int> out_rev;  // remainders collected (little-endian)

    // Repeated division algorithm to avoid overflow
    while (!source.empty()) {
        std::vector<unsigned int> next;
        unsigned int remainder = 0;

        for (auto d : source) {
            unsigned long long accum = remainder * static_cast<unsigned long long>(from_base) + d;
            unsigned int quotient_digit = static_cast<unsigned int>(accum / to_base);
            remainder = static_cast<unsigned int>(accum % to_base);

            if (!next.empty() || quotient_digit != 0) {
                next.push_back(quotient_digit);
            }
        }

        out_rev.push_back(remainder);
        source.swap(next);
    }

    // Reverse to big-endian order
    return std::vector<unsigned int>(out_rev.rbegin(), out_rev.rend());
}

}  // namespace all_your_base
