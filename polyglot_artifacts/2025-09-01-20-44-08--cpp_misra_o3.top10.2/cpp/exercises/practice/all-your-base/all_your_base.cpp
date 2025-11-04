#include "all_your_base.h"
#include <algorithm>
#include <stdexcept>

namespace all_your_base {

auto convert(std::uint32_t from_base,
             const std::vector<std::uint32_t>& input_digits,
             std::uint32_t to_base) -> std::vector<std::uint32_t>
{
    if(from_base < static_cast<std::uint32_t>(2U)) {
        throw std::invalid_argument("from_base must be >= 2");
    }

    if(to_base < static_cast<std::uint32_t>(2U)) {
        throw std::invalid_argument("to_base must be >= 2");
    }

    if(input_digits.empty()) {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    }

    /* Leading zeros (more than one digit with a leading 0) are not permitted */
    if((input_digits.size() > static_cast<std::size_t>(1U)) &&
       (input_digits.front() == static_cast<std::uint32_t>(0U))) {
        throw std::invalid_argument("input_digits contains leading zeros");
    }

    std::uint64_t value = static_cast<std::uint64_t>(0U);

    for(const std::uint32_t digit : input_digits) {
        if(digit >= from_base) {
            throw std::invalid_argument("digit out of range for from_base");
        }

        value = (value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(digit);
    }

    if(value == static_cast<std::uint64_t>(0U)) {
        return std::vector<std::uint32_t>{static_cast<std::uint32_t>(0U)};
    }

    std::vector<std::uint32_t> output_digits{};

    while(value > static_cast<std::uint64_t>(0U)) {
        const std::uint32_t remainder =
            static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(to_base));
        output_digits.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(output_digits.begin(), output_digits.end());

    return output_digits;
}

}  // namespace all_your_base
