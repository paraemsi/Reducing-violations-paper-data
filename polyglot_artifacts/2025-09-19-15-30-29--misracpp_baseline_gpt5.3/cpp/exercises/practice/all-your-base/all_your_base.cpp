#include "all_your_base.h"

#include <utility>
#include <algorithm>

namespace all_your_base {

namespace {
std::pair<std::vector<unsigned int>, unsigned int> divmod_base(
    const std::vector<unsigned int>& number,
    unsigned int in_base,
    unsigned int divisor_out_base) {
    std::vector<unsigned int> quotient;
    quotient.reserve(number.size());
    unsigned long long remainder = 0ULL;

    for (unsigned int d : number) {
        unsigned long long acc = remainder * static_cast<unsigned long long>(in_base)
                               + static_cast<unsigned long long>(d);
        unsigned int q = static_cast<unsigned int>(acc / divisor_out_base);
        remainder = acc % divisor_out_base;
        if (!quotient.empty() || q != 0U) {
            quotient.push_back(q);
        }
    }

    return {quotient, static_cast<unsigned int>(remainder)};
}
}  // namespace

std::vector<unsigned int> convert(unsigned int in_base, const std::vector<unsigned int>& digits, unsigned int out_base) {
    if (in_base < 2U) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (out_base < 2U) {
        throw std::invalid_argument("output base must be >= 2");
    }

    // Validate digits
    for (unsigned int d : digits) {
        if (d >= in_base) {
            throw std::invalid_argument("all digits must satisfy 0 <= d < input base");
        }
    }

    // Strip leading zeros
    auto first_non_zero = std::find_if(digits.begin(), digits.end(), [](unsigned int d) { return d != 0U; });
    if (first_non_zero == digits.end()) {
        return {};
    }
    std::vector<unsigned int> number(first_non_zero, digits.end());

    // Repeated division algorithm to avoid overflow
    std::vector<unsigned int> result;
    while (!number.empty()) {
        auto [quotient, remainder] = divmod_base(number, in_base, out_base);
        result.push_back(remainder);
        number = std::move(quotient);
    }

    // Reverse to most-significant-first
    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
