#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& input_digits,
                                  unsigned int output_base) {
    // Validate the bases.
    if (input_base < 2 || output_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // The input must contain at least one digit.
    if (input_digits.empty()) {
        throw std::invalid_argument("Input digit list cannot be empty");
    }

    // Validate digits and detect zero input.
    bool has_non_zero = false;
    for (unsigned int d : input_digits) {
        if (d >= input_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        if (d != 0) {
            has_non_zero = true;
        }
    }

    if (!has_non_zero) {
        return {0};
    }

    // Working copy of the input digits that we mutate during conversion.
    std::vector<unsigned int> work = input_digits;
    std::vector<unsigned int> output_digits;

    // Repeated-division algorithm that avoids constructing the entire value
    // in a built-in integer type, so it can handle arbitrarily large inputs.
    while (!work.empty()) {
        std::vector<unsigned int> quotient;
        unsigned int remainder = 0;

        for (unsigned int d : work) {
            unsigned long long accumulator =
                static_cast<unsigned long long>(remainder) * input_base + d;

            unsigned int q_digit = static_cast<unsigned int>(accumulator / output_base);
            remainder = static_cast<unsigned int>(accumulator % output_base);

            if (!quotient.empty() || q_digit != 0) {
                quotient.push_back(q_digit);
            }
        }

        output_digits.push_back(remainder);
        work.swap(quotient);
    }

    std::reverse(output_digits.begin(), output_digits.end());
    return output_digits;
}

}  // namespace all_your_base
