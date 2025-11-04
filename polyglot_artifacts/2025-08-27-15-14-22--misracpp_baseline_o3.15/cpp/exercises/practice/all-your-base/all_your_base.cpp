#include "all_your_base.h"
#include <algorithm>
#include <utility>

namespace all_your_base {

std::vector<unsigned int> convert(unsigned int from_base,
                                  const std::vector<unsigned int> &digits,
                                  unsigned int to_base) {
    // Validate bases
    if (from_base < 2 || to_base < 2) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    // Validate digits
    if (digits.empty()) {
        throw std::invalid_argument("Digits cannot be empty");
    }
    // Reject leading zeros (except for the single zero digit such as {0})
    if (digits.size() > 1 && digits.front() == 0) {
        throw std::invalid_argument("Digits cannot contain leading zeros");
    }

    // Validate each digit
    for (auto digit : digits) {
        if (digit >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    // If the input represents zero, return {0}
    if (std::all_of(digits.begin(), digits.end(),
                    [](unsigned int d) { return d == 0; })) {
        return {0};
    }

    // Repeated-division algorithm that avoids integer overflow.
    std::vector<unsigned int> source_digits = digits;  // working copy
    std::vector<unsigned int> result;

    while (!(source_digits.size() == 1 && source_digits[0] == 0)) {
        std::vector<unsigned int> next_digits;
        unsigned int remainder = 0;

        for (unsigned int d : source_digits) {
            unsigned long long acc =
                static_cast<unsigned long long>(remainder) * from_base + d;
            unsigned int quotient_digit = static_cast<unsigned int>(acc / to_base);
            remainder = static_cast<unsigned int>(acc % to_base);

            if (!next_digits.empty() || quotient_digit != 0) {
                next_digits.push_back(quotient_digit);
            }
        }

        // Prepend the remainder (current least-significant digit in target base)
        result.insert(result.begin(), remainder);

        if (next_digits.empty()) {
            next_digits.push_back(0);
        }
        source_digits = std::move(next_digits);
    }

    return result;
}

}  // namespace all_your_base
