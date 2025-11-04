#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>
#include <cstddef>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int in_base,
                                  const std::vector<unsigned int>& in_digits,
                                  unsigned int out_base) {
    if (in_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (out_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Validate digits and strip leading zeros
    std::size_t first_non_zero = 0;
    for (std::size_t i = 0; i < in_digits.size(); ++i) {
        const unsigned int d = in_digits[i];
        if (d >= in_base) {
            throw std::invalid_argument("all digits must be < input base");
        }
        if (first_non_zero == i && d == 0U) {
            ++first_non_zero;
        }
    }

    // If all digits are zero or input is empty, the value is zero.
    if (first_non_zero >= in_digits.size()) {
        return {0};
    }

    // Work on a trimmed copy without leading zeros.
    std::vector<unsigned int> digits(in_digits.begin() + static_cast<std::ptrdiff_t>(first_non_zero),
                                     in_digits.end());

    std::vector<unsigned int> result;

    // Repeated division algorithm to avoid overflow.
    while (!digits.empty()) {
        unsigned long long remainder = 0ULL;
        std::vector<unsigned int> next;
        next.reserve(digits.size());

        for (unsigned int d : digits) {
            unsigned long long acc = remainder * static_cast<unsigned long long>(in_base) + static_cast<unsigned long long>(d);
            unsigned int q = static_cast<unsigned int>(acc / static_cast<unsigned long long>(out_base));
            remainder = acc % static_cast<unsigned long long>(out_base);

            if (!next.empty() || q != 0U) {
                next.push_back(q);
            }
        }

        result.push_back(static_cast<unsigned int>(remainder));
        digits.swap(next);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
