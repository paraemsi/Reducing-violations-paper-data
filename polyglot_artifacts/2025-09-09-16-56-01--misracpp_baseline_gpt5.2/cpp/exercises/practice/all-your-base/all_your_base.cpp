#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(int input_base, const std::vector<unsigned int>& digits, int output_base) {
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Strip leading zeros
    auto it = std::find_if(digits.begin(), digits.end(), [](unsigned int d) { return d != 0U; });
    if (it == digits.end()) {
        return {0U};
    }
    std::vector<unsigned int> src(it, digits.end());

    // Validate digits
    for (unsigned int d : src) {
        if (d >= static_cast<unsigned int>(input_base)) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    std::vector<unsigned int> result;

    // Repeated division algorithm to avoid overflow
    while (!src.empty()) {
        std::vector<unsigned int> quotient;
        unsigned long long remainder = 0ULL;

        for (unsigned int d : src) {
            unsigned long long acc = remainder * static_cast<unsigned long long>(input_base)
                                     + static_cast<unsigned long long>(d);
            unsigned int qdigit = static_cast<unsigned int>(
                acc / static_cast<unsigned long long>(output_base)
            );
            remainder = acc % static_cast<unsigned long long>(output_base);

            if (!quotient.empty() || qdigit != 0U) {
                quotient.push_back(qdigit);
            }
        }

        result.push_back(static_cast<unsigned int>(remainder));
        src.swap(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}


}  // namespace all_your_base
