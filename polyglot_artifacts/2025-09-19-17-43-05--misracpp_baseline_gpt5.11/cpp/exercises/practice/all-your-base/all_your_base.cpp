#include "all_your_base.h"

#include <algorithm>
#include <limits>

namespace {

// Remove leading zeros, but do not convert an all-zero input into empty.
// The caller is responsible for interpreting empty vs zero.
std::vector<unsigned int> strip_leading_zeros(const std::vector<unsigned int>& digits) {
    auto it = std::find_if(digits.begin(), digits.end(), [](unsigned int d) { return d != 0u; });
    if (it == digits.end()) {
        return {}; // all zeros -> represent as empty; caller will translate to {0}
    }
    return std::vector<unsigned int>(it, digits.end());
}

void validate_bases(int from_base, int to_base) {
    if (from_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (to_base < 2) {
        throw std::invalid_argument("output base must be >= 2");
    }
}

void validate_digits(const std::vector<unsigned int>& digits, int from_base) {
    if (from_base < 2) {
        throw std::invalid_argument("input base must be >= 2");
    }
    for (unsigned int d : digits) {
        if (d >= static_cast<unsigned int>(from_base)) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }
}

// Perform one step of long division of a number represented in base `from_base` by `divisor`.
// Returns the quotient digits (in base `from_base`) and sets `remainder` in [0, divisor).
std::vector<unsigned int> divmod(const std::vector<unsigned int>& number,
                                 unsigned int from_base,
                                 unsigned int divisor,
                                 unsigned int& remainder) {
    std::vector<unsigned int> quotient;
    quotient.reserve(number.size());

    unsigned long long rem = 0ull;
    for (unsigned int d : number) {
        unsigned long long acc = rem * static_cast<unsigned long long>(from_base) + static_cast<unsigned long long>(d);
        unsigned int q_digit = static_cast<unsigned int>(acc / divisor);
        rem = acc % divisor;
        quotient.push_back(q_digit);
    }
    remainder = static_cast<unsigned int>(rem);

    // strip leading zeros from quotient
    auto it = std::find_if(quotient.begin(), quotient.end(), [](unsigned int qd) { return qd != 0u; });
    if (it == quotient.end()) {
        return {};
    }
    return std::vector<unsigned int>(it, quotient.end());
}

std::vector<unsigned int> convert_impl(const std::vector<unsigned int>& input_digits, int from_base, int to_base) {
    validate_bases(from_base, to_base);
    validate_digits(input_digits, from_base);

    // Normalize input by removing leading zeros.
    std::vector<unsigned int> digits = strip_leading_zeros(input_digits);

    // If value is zero (empty after stripping), return {0}
    if (digits.empty()) {
        return {0u};
    }

    std::vector<unsigned int> result_reversed;
    result_reversed.reserve(input_digits.size()); // heuristic

    unsigned int divisor = static_cast<unsigned int>(to_base);
    unsigned int fb = static_cast<unsigned int>(from_base);

    // Repeatedly divide by the output base and collect remainders.
    while (!digits.empty()) {
        unsigned int remainder = 0u;
        digits = divmod(digits, fb, divisor, remainder);
        result_reversed.push_back(remainder);
    }

    // Reverse to get the correct order.
    std::reverse(result_reversed.begin(), result_reversed.end());
    return result_reversed;
}

} // unnamed namespace

namespace all_your_base {


std::vector<unsigned int> convert(int from_base, const std::vector<unsigned int>& digits, int to_base) {
    return convert_impl(digits, from_base, to_base);
}

std::vector<unsigned int> convert(const std::vector<unsigned int>& digits, int from_base, int to_base) {
    return convert_impl(digits, from_base, to_base);
}

}  // namespace all_your_base
