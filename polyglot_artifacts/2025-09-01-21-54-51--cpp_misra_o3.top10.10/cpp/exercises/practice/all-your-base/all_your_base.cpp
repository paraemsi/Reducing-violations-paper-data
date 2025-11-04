#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>
#include <cstdint>

namespace all_your_base {

auto convert(base_int_t from_base,
             const std::vector<base_int_t>& in_digits,
             base_int_t to_base) -> std::vector<base_int_t>
{
    if ((from_base < static_cast<base_int_t>(2)) || (to_base < static_cast<base_int_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if (in_digits.empty()) {
        throw std::invalid_argument("Input digit list is empty");
    }

    std::uint64_t value = static_cast<std::uint64_t>(0U);

    for (const base_int_t digit : in_digits) {
        if ((digit < static_cast<base_int_t>(0)) || (digit >= from_base)) {
            throw std::invalid_argument("Digit not valid for given base");
        }
        value = ((value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(digit));
    }

    if (value == static_cast<std::uint64_t>(0U)) {
        return std::vector<base_int_t>{static_cast<base_int_t>(0)};
    }

    std::vector<base_int_t> out_digits;

    while (value > static_cast<std::uint64_t>(0U)) {
        const base_int_t remainder =
            static_cast<base_int_t>(value % static_cast<std::uint64_t>(to_base));
        out_digits.push_back(remainder);
        value /= static_cast<std::uint64_t>(to_base);
    }

    std::reverse(out_digits.begin(), out_digits.end());
    return out_digits;
}

}  // namespace all_your_base
