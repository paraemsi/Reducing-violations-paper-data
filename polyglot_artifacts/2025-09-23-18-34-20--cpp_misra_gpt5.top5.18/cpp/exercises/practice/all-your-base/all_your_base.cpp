#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert_u32(std::uint32_t in_base,
                                       const std::vector<std::uint32_t>& digits,
                                       std::uint32_t out_base) noexcept(false) {
    static constexpr std::uint32_t kZero = static_cast<std::uint32_t>(0);
    static constexpr std::uint32_t kTwo = static_cast<std::uint32_t>(2);

    if ((in_base < kTwo) || (out_base < kTwo)) {
        throw std::invalid_argument("base must be >= 2");
    }

    // Trim leading zeros
    std::size_t first_non_zero = static_cast<std::size_t>(0);
    while ((first_non_zero < digits.size()) && (digits[first_non_zero] == kZero)) {
        first_non_zero = first_non_zero + static_cast<std::size_t>(1);
    }

    // If empty or all zeros -> represent zero in target base
    if (first_non_zero == digits.size()) {
        return std::vector<std::uint32_t>{kZero};
    }

    // Validate digits and copy the significant part
    std::vector<std::uint32_t> source;
    source.reserve(digits.size() - first_non_zero);
    for (std::size_t i = first_non_zero; i < digits.size(); i = i + static_cast<std::size_t>(1)) {
        const std::uint32_t d = static_cast<std::uint32_t>(digits[i]);
        if (d >= in_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
        source.push_back(d);
    }

    std::vector<std::uint32_t> result;

    // Repeated division algorithm: convert without overflow
    while (!source.empty()) {
        std::vector<std::uint32_t> quotient;
        quotient.reserve(source.size());

        std::uint32_t remainder = kZero;

        for (std::size_t i = static_cast<std::size_t>(0); i < source.size(); i = i + static_cast<std::size_t>(1)) {
            const std::uint32_t d = source[i];
            const std::uint32_t acc = (remainder * in_base) + d;

            const std::uint32_t qdigit = acc / out_base;
            remainder = acc % out_base;

            if ((!quotient.empty()) || (qdigit != kZero)) {
                quotient.push_back(qdigit);
            }
        }

        result.push_back(remainder);
        source.swap(quotient);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
