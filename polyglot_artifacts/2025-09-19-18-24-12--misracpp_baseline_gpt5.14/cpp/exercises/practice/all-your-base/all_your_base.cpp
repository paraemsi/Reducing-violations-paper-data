#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int in_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int out_base) {
    if (in_base < 2U) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (out_base < 2U) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Validate digits and strip leading zeros
    std::vector<unsigned int> input;
    input.reserve(digits.size());
    if (digits.empty()) {
        return std::vector<unsigned int>{};
    }
    bool leading = true;
    for (unsigned int d : digits) {
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        if (leading && d == 0U) {
            continue;
        }
        leading = false;
        input.push_back(d);
    }

    if (input.empty()) {
        return std::vector<unsigned int>{0U};
    }

    std::vector<unsigned int> result;
    std::vector<unsigned int> source = input;

    // Repeated division algorithm to avoid overflow
    while (!source.empty()) {
        std::vector<unsigned int> quotient;
        quotient.reserve(source.size());
        unsigned long long remainder = 0ULL;

        for (unsigned int d : source) {
            unsigned long long acc = remainder * static_cast<unsigned long long>(in_base) + d;
            unsigned int q = static_cast<unsigned int>(acc / out_base);
            remainder = acc % out_base;
            quotient.push_back(q);
        }

        // Push remainder (next least-significant digit in output base)
        result.push_back(static_cast<unsigned int>(remainder));

        // Strip leading zeros from quotient to prepare next iteration
        std::size_t first_nz = 0;
        while (first_nz < quotient.size() && quotient[first_nz] == 0U) {
            ++first_nz;
        }
        source.assign(quotient.begin() + static_cast<std::ptrdiff_t>(first_nz),
                      quotient.end());
    }

    // Remainders collected least-significant first; reverse to most-significant first
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
