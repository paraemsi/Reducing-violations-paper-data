#include "all_your_base.h"
#include <cstdint>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base) {
    if (from_base <= 1 || to_base <= 1) {
        throw std::invalid_argument("Bases must be greater than 1");
    }

    if (digits.empty()) {
        throw std::invalid_argument("Digits vector may not be empty");
    }

    bool all_zero = true;
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        if (d != 0u) {
            all_zero = false;
        }
    }

    if (all_zero) {
        return {0};
    }

    // Accumulate the value in an unsigned 64-bit integer.
    // The exercise's test cases remain within this range.
    uint64_t value = 0;
    for (auto d : digits) {
        value = value * static_cast<uint64_t>(from_base) +
                static_cast<uint64_t>(d);
    }

    std::vector<unsigned int> result;
    while (value > 0) {
        result.insert(result.begin(),
                      static_cast<unsigned int>(value % static_cast<uint64_t>(to_base)));
        value /= static_cast<uint64_t>(to_base);
    }

    return result;
}

}  // namespace all_your_base
