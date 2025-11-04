#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

sequence convert(const integer input_base,
                 const sequence& digits,
                 const integer output_base) {
    if ((input_base < 2)) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if ((output_base < 2)) {
        throw std::invalid_argument("output base must be >= 2");
    }

    std::uint64_t value_in_base10 = 0;
    for (const integer digit : digits) {
        if ((digit >= input_base)) {
            throw std::invalid_argument("all digits must be smaller than input base");
        }
        value_in_base10 = ((value_in_base10 * input_base) + digit);
    }

    if ((value_in_base10 == 0)) {
        return {integer{0}};
    }

    sequence output_digits;
    while ((value_in_base10 > 0)) {
        output_digits.push_back(
            static_cast<integer>(value_in_base10 % output_base));
        value_in_base10 = value_in_base10 / output_base;
    }

    std::reverse(output_digits.begin(), output_digits.end());

    return output_digits;
}

}  // namespace all_your_base
