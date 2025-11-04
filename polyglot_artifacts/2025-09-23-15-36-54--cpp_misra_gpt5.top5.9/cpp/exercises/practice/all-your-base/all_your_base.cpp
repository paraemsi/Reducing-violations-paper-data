#include "all_your_base.h"

#include <stdexcept>
#include <algorithm>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base,
                                   const std::vector<std::uint32_t>& digits,
                                   std::uint32_t output_base)
{
    if ((input_base < static_cast<std::uint32_t>(2U)) || (output_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("base must be >= 2");
    }

    // Trim leading zeros
    std::size_t start = 0U;
    while ((start < digits.size()) && (digits[start] == static_cast<std::uint32_t>(0U))) {
        start = start + 1U;
    }
    if (start == digits.size()) {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    }

    // Validate digits
    for (std::size_t i = start; i < digits.size(); ++i) {
        const std::uint32_t d = digits[i];
        if (d >= input_base) {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    // Result stored least-significant digit first in output base
    std::vector<std::uint32_t> result;

    for (std::size_t i = start; i < digits.size(); ++i) {
        const std::uint32_t d = digits[i];

        // Multiply result by input_base (in output_base representation)
        std::uint64_t carry_mul = static_cast<std::uint64_t>(0U);
        for (std::size_t j = 0U; j < result.size(); ++j) {
            const std::uint64_t prod =
                ((static_cast<std::uint64_t>(result[j]) * static_cast<std::uint64_t>(input_base)) + carry_mul);
            const std::uint64_t rem64 = (prod % static_cast<std::uint64_t>(output_base));
            result[j] = static_cast<std::uint32_t>(rem64);
            carry_mul = (prod / static_cast<std::uint64_t>(output_base));
        }
        while (carry_mul > static_cast<std::uint64_t>(0U)) {
            const std::uint64_t rem64 = (carry_mul % static_cast<std::uint64_t>(output_base));
            result.push_back(static_cast<std::uint32_t>(rem64));
            carry_mul = (carry_mul / static_cast<std::uint64_t>(output_base));
        }

        // Add the next digit d
        std::uint64_t carry_add = static_cast<std::uint64_t>(d);
        std::size_t j = 0U;
        while ((carry_add > static_cast<std::uint64_t>(0U)) && (j < result.size())) {
            const std::uint64_t sum = static_cast<std::uint64_t>(result[j]) + carry_add;
            const std::uint64_t rem64 = (sum % static_cast<std::uint64_t>(output_base));
            result[j] = static_cast<std::uint32_t>(rem64);
            carry_add = (sum / static_cast<std::uint64_t>(output_base));
            j = j + 1U;
        }
        while (carry_add > static_cast<std::uint64_t>(0U)) {
            const std::uint64_t rem64 = (carry_add % static_cast<std::uint64_t>(output_base));
            result.push_back(static_cast<std::uint32_t>(rem64));
            carry_add = (carry_add / static_cast<std::uint64_t>(output_base));
        }
    }

    // Convert to most-significant digit first
    std::reverse(result.begin(), result.end());

    return result;
}

}  // namespace all_your_base
