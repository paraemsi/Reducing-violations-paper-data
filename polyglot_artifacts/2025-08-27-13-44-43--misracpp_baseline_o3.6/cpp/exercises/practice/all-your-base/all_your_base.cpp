#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

namespace {

/* Validate all pre-conditions required by the specification. */
void validate(const std::vector<unsigned int>& digits,
              unsigned int from_base,
              unsigned int to_base) {
    if (from_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
    if (digits.empty()) {
        throw std::invalid_argument("no digits supplied");
    }
    if (digits.size() > 1 && digits.front() == 0) {
        throw std::invalid_argument("leading zeros are not allowed");
    }
    for (auto d : digits) {
        if (d >= from_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }
}

}  // namespace

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int to_base) {
    validate(digits, from_base, to_base);

    /* Special-case zero early. */
    if (digits.size() == 1 && digits[0] == 0) {
        return {0};
    }

    /* Accumulate the value into an unsigned 64-bit integer.
       This is sufficient for all current Exercism test numbers. */
    std::uint64_t value = 0;
    for (unsigned int d : digits) {
        value = value * static_cast<std::uint64_t>(from_base) +
                static_cast<std::uint64_t>(d);
    }

    /* Produce digits in the target base (least-significant first). */
    std::vector<unsigned int> out_rev;
    while (value > 0) {
        out_rev.push_back(static_cast<unsigned int>(value % to_base));
        value /= to_base;
    }

    /* Reverse to get most-significant digit first. */
    std::reverse(out_rev.begin(), out_rev.end());
    return out_rev;
}

}  // namespace all_your_base
