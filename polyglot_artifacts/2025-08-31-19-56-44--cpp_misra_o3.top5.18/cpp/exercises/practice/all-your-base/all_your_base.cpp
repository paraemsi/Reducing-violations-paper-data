#include "all_your_base.h"
#include <vector>
#include <cstdint>
#include <stdexcept>
#include <algorithm>
#include <cstddef>

namespace all_your_base {

auto convert(std::uint32_t input_base,
             const std::vector<std::uint32_t>& digits,
             std::uint32_t output_base) -> std::vector<std::uint32_t>
{
    if ((input_base < static_cast<std::uint32_t>(2U)) || (output_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (digits.empty() == true) {
        throw std::invalid_argument("Digits vector is empty");
    }


    std::uint64_t value = static_cast<std::uint64_t>(0U);

    for (auto const digit : digits) {
        if (digit >= input_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
        value = (value * static_cast<std::uint64_t>(input_base)) + static_cast<std::uint64_t>(digit);
    }

    if (value == static_cast<std::uint64_t>(0U)) {
        return { static_cast<std::uint32_t>(0U) };
    }

    std::vector<std::uint32_t> result {};

    while (value > static_cast<std::uint64_t>(0U)) {
        std::uint32_t remainder = static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(output_base));
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(output_base);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

}  // namespace all_your_base
