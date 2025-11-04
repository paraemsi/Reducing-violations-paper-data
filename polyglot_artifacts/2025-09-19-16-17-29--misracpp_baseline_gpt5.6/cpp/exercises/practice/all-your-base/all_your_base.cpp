#include "all_your_base.h"

#include <algorithm>
#include <vector>
#include <stdexcept>

namespace all_your_base {

namespace {
bool is_valid_base(unsigned int base) {
    return base >= 2;
}

bool are_valid_digits(const std::vector<unsigned int>& digits, unsigned int base) {
    for (auto d : digits) {
        if (d >= base) return false;
    }
    return true;
}

std::vector<unsigned int> strip_leading_zeros(const std::vector<unsigned int>& digits) {
    auto it = std::find_if(digits.begin(), digits.end(),
                           [](unsigned int d) { return d != 0; });
    if (it == digits.end()) {
        return {};
    }
    return std::vector<unsigned int>(it, digits.end());
}

std::vector<unsigned int> convert_impl(const std::vector<unsigned int>& digits,
                                       unsigned int input_base,
                                       unsigned int output_base) {
    if (!is_valid_base(input_base) || !is_valid_base(output_base)) throw std::invalid_argument("invalid base");
    if (!are_valid_digits(digits, input_base)) throw std::invalid_argument("invalid digit");

    // Normalize input by removing leading zeros
    std::vector<unsigned int> current = strip_leading_zeros(digits);

    // If number is zero, return empty vector
    if (current.empty()) {
        return {};
    }

    std::vector<unsigned int> result;

    // Repeated division algorithm: divide the number (in input_base) by output_base
    // collecting remainders to form the output digits.
    while (!current.empty()) {
        std::vector<unsigned int> quotient;
        quotient.reserve(current.size());
        unsigned long long acc = 0ULL;

        for (unsigned int d : current) {
            acc = acc * input_base + d;
            unsigned int qdigit = static_cast<unsigned int>(acc / output_base);
            acc = acc % output_base;
            if (!quotient.empty() || qdigit != 0) {
                quotient.push_back(qdigit);
            }
        }

        // Remainder is the next output digit (in reverse order)
        result.push_back(static_cast<unsigned int>(acc));

        // Prepare for next iteration
        current = std::move(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}
}  // namespace

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& digits,
                                  unsigned int output_base) {
    return convert_impl(digits, input_base, output_base);
}

std::vector<unsigned int> convert(const std::vector<unsigned int>& digits,
                                  unsigned int input_base,
                                  unsigned int output_base) {
    return convert_impl(digits, input_base, output_base);
}

}  // namespace all_your_base
