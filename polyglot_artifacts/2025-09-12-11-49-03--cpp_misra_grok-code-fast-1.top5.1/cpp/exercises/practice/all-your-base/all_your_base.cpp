#include "all_your_base.h"

#include <vector>
#include <cstdint>
#include <stdexcept>

std::vector<std::uint32_t> all_your_base::convert(std::uint32_t input_base, const std::vector<std::uint32_t>& digits, std::uint32_t output_base) {
    if (input_base < 2U) {
        throw std::invalid_argument("input base must be >= 2");
    }
    if (output_base < 2U) {
        throw std::invalid_argument("output base must be >= 2");
    }
    if (digits.empty()) {
        throw std::invalid_argument("digits cannot be empty");
    }
    for (const auto& digit : digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("all digits must be < input base");
        }
    }

    // Step 1: Convert from input_base to decimal (base 10) representation
    std::uint64_t decimal_value = 0U;
    for (auto it = digits.rbegin(); it != digits.rend(); ++it) {
        decimal_value = (decimal_value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(*it);
    }

    // Step 2: Convert from decimal to output_base
    std::vector<std::uint32_t> result;
    if (decimal_value == 0U) {
        result.push_back(0U);
    } else {
        while (decimal_value > 0U) {
            std::uint32_t digit = static_cast<std::uint32_t>((decimal_value % static_cast<std::uint64_t>(output_base)));
            result.insert(result.begin(), digit);
            decimal_value = (decimal_value / static_cast<std::uint64_t>(output_base));
        }
    }

    return result;
}
