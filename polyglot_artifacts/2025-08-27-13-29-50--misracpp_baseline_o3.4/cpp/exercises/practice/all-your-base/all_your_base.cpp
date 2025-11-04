#include "all_your_base.h"

#include <algorithm> // std::reverse
#include <cstdint>   // std::uint64_t
#include <utility>   // std::move

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int> &digits,
                                  unsigned int to_base) {
    // Validate bases
    if (from_base < 2 || to_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (digits.empty()) {
        throw std::invalid_argument("Digits vector may not be empty");
    }

    // Validate digits and strip leading zeros
    std::vector<unsigned int> input;
    input.reserve(digits.size());
    bool non_zero_found = false;
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        if (d != 0 || non_zero_found) {
            input.push_back(d);
            non_zero_found = true;
        }
    }

    // If all digits were zero, the value is zero.
    if (!non_zero_found) {
        return {0};
    }

    // If the bases are the same, return the (trimmed) digits.
    if (from_base == to_base) {
        return input;
    }

    // Repeated-division algorithm to avoid overflow
    std::vector<unsigned int> output_reversed;
    while (!input.empty()) {
        std::vector<unsigned int> next;
        next.reserve(input.size());
        std::uint64_t remainder = 0;
        bool started = false;

        for (auto d : input) {
            std::uint64_t accumulator = remainder * from_base + d;
            unsigned int quotient_digit =
                static_cast<unsigned int>(accumulator / to_base);
            remainder = static_cast<unsigned int>(accumulator % to_base);

            if (quotient_digit != 0 || started) {
                next.push_back(quotient_digit);
                started = true;
            }
        }

        output_reversed.push_back(static_cast<unsigned int>(remainder));
        input = std::move(next);
    }

    std::reverse(output_reversed.begin(), output_reversed.end());
    return output_reversed;
}

}  // namespace all_your_base
