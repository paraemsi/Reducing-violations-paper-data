#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int in_base, const std::vector<unsigned int>& in_digits, unsigned int out_base) {
    if (in_base < 2 || out_base < 2) {
        throw std::invalid_argument("base must be >= 2");
    }

    // Validate digits: each must be less than the input base.
    if (!std::all_of(in_digits.begin(), in_digits.end(),
                     [in_base](unsigned int d) { return d < in_base; })) {
        throw std::invalid_argument("digit out of range for input base");
    }

    // Trim leading zeros.
    std::size_t first_non_zero = 0;
    while (first_non_zero < in_digits.size() && in_digits[first_non_zero] == 0) {
        ++first_non_zero;
    }
    if (first_non_zero == in_digits.size()) {
        return {};
    }

    // Long-division style base conversion to avoid overflow.
    std::vector<unsigned int> source(in_digits.begin() + static_cast<std::ptrdiff_t>(first_non_zero), in_digits.end());
    std::vector<unsigned int> result;

    while (!source.empty()) {
        std::vector<unsigned int> quotient;
        quotient.reserve(source.size());
        unsigned long long carry = 0;

        for (unsigned int d : source) {
            unsigned long long acc = carry * static_cast<unsigned long long>(in_base) + d;
            unsigned int q = static_cast<unsigned int>(acc / out_base);
            carry = acc % out_base;
            if (!quotient.empty() || q != 0) {
                quotient.push_back(q);
            }
        }

        result.push_back(static_cast<unsigned int>(carry));
        source = std::move(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
