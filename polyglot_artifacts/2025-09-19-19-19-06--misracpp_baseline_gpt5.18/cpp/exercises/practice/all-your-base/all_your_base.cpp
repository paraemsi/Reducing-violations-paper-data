#include "all_your_base.h"

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

std::vector<unsigned int> convert(int input_base,
                                  const std::vector<unsigned int>& in_digits,
                                  int output_base) {
    if (input_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Strip leading zeros
    std::size_t first_non_zero = 0;
    while (first_non_zero < in_digits.size() && in_digits[first_non_zero] == 0) {
        ++first_non_zero;
    }

    std::vector<unsigned int> digits(in_digits.begin() + first_non_zero, in_digits.end());

    // If all digits were zeros or input was empty, the value is zero.
    if (digits.empty()) {
        return {0};
    }

    // Validate digits against input base
    for (unsigned int d : digits) {
        if (d >= static_cast<unsigned int>(input_base)) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    // Convert using repeated division algorithm (no big integers required).
    std::vector<unsigned int> result;
    std::vector<unsigned int> current = digits;

    while (!current.empty()) {
        std::vector<unsigned int> next;
        next.reserve(current.size());

        std::uint64_t remainder = 0;
        for (unsigned int d : current) {
            std::uint64_t acc = remainder * static_cast<std::uint64_t>(input_base) + d;
            unsigned int qdigit =
                static_cast<unsigned int>(acc / static_cast<std::uint64_t>(output_base));
            remainder = acc % static_cast<std::uint64_t>(output_base);

            if (!next.empty() || qdigit != 0) {
                next.push_back(qdigit);
            }
        }

        result.push_back(static_cast<unsigned int>(remainder));
        current.swap(next);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
