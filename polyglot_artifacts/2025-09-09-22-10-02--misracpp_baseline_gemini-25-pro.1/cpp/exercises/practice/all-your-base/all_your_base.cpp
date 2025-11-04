#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                 const std::vector<unsigned int>& digits,
                                 unsigned int output_base) {
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    if (digits.empty()) {
        throw std::invalid_argument("input digits must not be empty");
    }
    if (digits.front() == 0 && digits.size() > 1) {
        throw std::invalid_argument("input digits must not have leading zeros");
    }

    unsigned long long number_base10 = 0;
    for (unsigned int digit : digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must be smaller than input base");
        }
        number_base10 = number_base10 * input_base + digit;
    }

    if (number_base10 == 0) {
        return {0};
    }

    std::vector<unsigned int> output_digits;
    while (number_base10 > 0) {
        output_digits.push_back(number_base10 % output_base);
        number_base10 /= output_base;
    }

    std::reverse(output_digits.begin(), output_digits.end());
    return output_digits;
}

}  // namespace all_your_base
