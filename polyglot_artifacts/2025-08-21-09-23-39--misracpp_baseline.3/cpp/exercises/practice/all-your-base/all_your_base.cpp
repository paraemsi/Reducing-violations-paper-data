#include "all_your_base.h"

#include <vector>
#include <stdexcept>
#include <algorithm>

namespace all_your_base {

    std::vector<unsigned int> convert(
        unsigned int input_base,
        std::vector<unsigned int> const& digits,
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
        auto it = digits.begin();
        while (it != digits.end() && *it == 0) ++it;
        std::vector<unsigned int> clean_digits(it, digits.end());

        // Special case: input is zero
        if (clean_digits.empty()) {
            return {};
        }

        // Convert input digits to integer value
        unsigned long long value = 0;
        for (auto d : clean_digits) {
            value = value * input_base + d;
        }

        // If the value is zero and the input had at least one digit, return empty vector
        if (value == 0) {
            return {};
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
