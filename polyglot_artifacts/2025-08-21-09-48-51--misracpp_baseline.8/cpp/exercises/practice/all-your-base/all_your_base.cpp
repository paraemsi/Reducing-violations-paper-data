#include "all_your_base.h"

#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<unsigned int> convert(
    unsigned int input_base,
    const std::vector<unsigned int>& digits,
    unsigned int output_base
) {
    // Validate bases
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Validate digits
    bool leading = true;
    for (auto d : digits) {
        if (leading && d == 0) continue;
        leading = false;
        if (d >= input_base) {
            throw std::invalid_argument("all digits must be < input base");
        }
    }

    // Remove leading zeros
    auto first_nonzero = std::find_if(digits.begin(), digits.end(), [](unsigned int d){ return d != 0; });
    std::vector<unsigned int> clean_digits(first_nonzero, digits.end());

    // If the input is empty or all zeros, return empty vector
    if (digits.empty() || clean_digits.empty()) {
        return {};
    }

    // Convert input digits to an integer value
    unsigned long long value = 0;
    for (auto d : clean_digits) {
        value = value * input_base + d;
    }

    // Convert integer value to output_base digits
    std::vector<unsigned int> result;
    while (value > 0) {
        result.push_back(value % output_base);
        value /= output_base;
    }
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
