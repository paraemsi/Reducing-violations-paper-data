#include "all_your_base.h"
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base) {
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (digits.empty()) {
        throw std::invalid_argument("No digits provided");
    }
    /* Leading zeros are not allowed unless the number itself is zero. */
    if (digits.size() > 1 && digits.front() == 0) {
        throw std::invalid_argument("Leading zeros are not allowed");
    }

    std::uint64_t value = 0;
    for (unsigned int digit : digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        value = value * input_base + digit;
    }

    if (value == 0) {
        return {0};
    }

    std::vector<unsigned int> result;
    while (value > 0) {
        result.insert(result.begin(), static_cast<unsigned int>(value % output_base));
        value /= output_base;
    }
    return result;
}

}  // namespace all_your_base
