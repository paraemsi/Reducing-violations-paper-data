#include "all_your_base.h"

#include <vector>
#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

using digit_t = std::uint32_t;
using base_t  = std::uint32_t;
/*  External I/O type alias (kept in sync with header). */
using digit_io_t = unsigned int;

static auto convert_impl(const std::vector<digit_t>& digits,
                         base_t from_base,
                         base_t to_base) -> std::vector<digit_t>
{
    std::vector<digit_t> result{};

    if((from_base < static_cast<base_t>(2)) || (to_base < static_cast<base_t>(2))) {
        return result;
    }

    std::size_t start_index = static_cast<std::size_t>(0);
    while((start_index < digits.size()) && (digits[start_index] == static_cast<digit_t>(0))) {
        start_index = start_index + static_cast<std::size_t>(1);
    }

    if(start_index == digits.size()) {
        result.push_back(static_cast<digit_t>(0));
        return result;
    }

    std::int64_t value = static_cast<std::int64_t>(0);

    for(std::size_t i = start_index; i < digits.size(); i = i + static_cast<std::size_t>(1)) {
        const digit_t current_digit = digits[i];

        if(current_digit >= from_base) {
            return std::vector<digit_t>{};
        }

        value = ((value * static_cast<std::int64_t>(from_base))
                + static_cast<std::int64_t>(current_digit));
    }

    while(value > static_cast<std::int64_t>(0)) {
        const digit_t remainder =
            static_cast<digit_t>(value % static_cast<std::int64_t>(to_base));
        result.push_back(remainder);
        value = value / static_cast<std::int64_t>(to_base);
    }

    std::reverse(result.begin(), result.end());
    return result;
}

auto convert(digit_io_t from_base,
             const std::vector<digit_io_t>& digits,
             digit_io_t to_base) -> std::vector<digit_io_t>
{
    if((from_base < static_cast<digit_io_t>(2)) || (to_base < static_cast<digit_io_t>(2))) {
        throw std::invalid_argument("base must be >= 2");
    }

    std::vector<digit_t> internal_digits{};
    internal_digits.reserve(digits.size());
    for(digit_io_t d : digits) {
        if(d >= from_base) {
            throw std::invalid_argument("digit out of range for base");
        }
        internal_digits.push_back(static_cast<digit_t>(d));
    }

    const std::vector<digit_t> internal_result =
        convert_impl(internal_digits,
                     static_cast<base_t>(from_base),
                     static_cast<base_t>(to_base));

    std::vector<digit_io_t> result{};
    result.reserve(internal_result.size());
    for(digit_t d : internal_result) {
        result.push_back(static_cast<digit_io_t>(d));
    }
    return result;
}

}  // namespace all_your_base
