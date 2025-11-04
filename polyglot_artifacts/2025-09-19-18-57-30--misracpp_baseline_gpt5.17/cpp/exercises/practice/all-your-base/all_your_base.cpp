#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

namespace {
std::vector<unsigned int> convert_impl(const std::vector<unsigned int>& digits,
                                       int input_base,
                                       int output_base) {
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digits and strip leading zeros
    std::vector<unsigned int> trimmed;
    trimmed.reserve(digits.size());
    bool leading = true;
    for (unsigned int d : digits) {
        if (d >= static_cast<unsigned int>(input_base)) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        if (leading) {
            if (d == 0) continue;
            leading = false;
        }
        if (!leading) {
            trimmed.push_back(d);
        }
    }

    // If the value is zero, represent it as an empty sequence per tests
    if (trimmed.empty()) {
        return {};
    }

    // Repeated long division algorithm to avoid big integer overflow
    std::vector<unsigned int> result;
    std::vector<unsigned int> number = trimmed;

    while (!number.empty()) {
        unsigned int remainder = 0;
        std::vector<unsigned int> quotient;
        quotient.reserve(number.size());

        for (unsigned int d : number) {
            unsigned long long acc =
                static_cast<unsigned long long>(remainder) * static_cast<unsigned long long>(input_base)
                + static_cast<unsigned long long>(d);
            unsigned int q = static_cast<unsigned int>(acc / static_cast<unsigned long long>(output_base));
            remainder = static_cast<unsigned int>(acc % static_cast<unsigned long long>(output_base));
            if (!quotient.empty() || q != 0) {
                quotient.push_back(q);
            }
        }

        result.push_back(remainder);
        number.swap(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}
}  // namespace

std::vector<unsigned int> convert(const std::vector<unsigned int>& digits,
                                  int input_base,
                                  int output_base) {
    return convert_impl(digits, input_base, output_base);
}

std::vector<unsigned int> convert(int input_base,
                                  const std::vector<unsigned int>& digits,
                                  int output_base) {
    return convert_impl(digits, input_base, output_base);
}


}  // namespace all_your_base
