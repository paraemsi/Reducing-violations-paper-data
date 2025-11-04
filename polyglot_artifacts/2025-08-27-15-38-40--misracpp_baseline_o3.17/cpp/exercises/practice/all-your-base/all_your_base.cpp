#include "all_your_base.h"

#include <algorithm> // std::reverse

namespace all_your_base {

static void validate_input(const std::vector<unsigned int>& digits,
                           int from_base,
                           int to_base)
{
    if (from_base < 2 || to_base < 2) {
        throw std::invalid_argument("bases must be >= 2");
    }
    if (digits.empty()) {
        throw std::invalid_argument("digits may not be empty");
    }
    for (unsigned int d : digits) {
        if (d >= static_cast<unsigned int>(from_base)) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }
    // Leading zeros are permitted.  They do not affect the numeric value.
}

static unsigned long long to_base10(const std::vector<unsigned int>& digits,
                                    int from_base)
{
    unsigned long long value = 0;
    for (unsigned int d : digits) {
        value = value * static_cast<unsigned long long>(from_base)
              + static_cast<unsigned long long>(d);
    }
    return value;
}

static std::vector<unsigned int> from_base10(unsigned long long value, int to_base)
{
    if (value == 0) {
        return {0};
    }

    std::vector<unsigned int> out;
    while (value > 0) {
        out.push_back(static_cast<unsigned int>(value % to_base));
        value /= to_base;
    }
    std::reverse(out.begin(), out.end());
    return out;
}

std::vector<unsigned int> convert(int from_base,
                                  const std::vector<unsigned int>& digits,
                                  int to_base)
{
    validate_input(digits, from_base, to_base);
    const auto value = to_base10(digits, from_base);
    return from_base10(value, to_base);
}

}  // namespace all_your_base
