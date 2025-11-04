#include "all_your_base.h"
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <cstdint>

namespace all_your_base {

std::vector<unsigned int> convert(int from_base, const std::vector<unsigned int>& digits, int to_base) {
    // Validate bases
    if (from_base < 2 || to_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (digits.empty()) {
        throw std::invalid_argument("Digit list cannot be empty");
    }

    // Validate digits
    for (int d : digits) {
        if (d < 0 || d >= from_base) {
            throw std::invalid_argument("Invalid digit in input");
        }
    }

    // Special-case zero
    bool is_zero = std::all_of(digits.begin(), digits.end(),
                               [](unsigned int d) { return d == 0; });
    if (is_zero) {
        return {0};
    }

    // Convert input digits to integer value
    std::uint64_t value = 0;
    for (unsigned int d : digits) {
        value = value * static_cast<std::uint64_t>(from_base)
                + static_cast<std::uint64_t>(d);
    }

    // Convert integer value to target base
    std::vector<unsigned int> result;
    while (value > 0) {
        unsigned int remainder = static_cast<unsigned int>(value % to_base);
        result.push_back(remainder);
        value /= to_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
