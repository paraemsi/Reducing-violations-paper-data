#include "all_your_base.h"

#include <algorithm>
#include <stdexcept>

namespace all_your_base {

namespace detail {

auto convert_impl(digit_t                     from_base,
                  std::vector<digit_t> const& digits,
                  digit_t                     to_base) -> std::vector<digit_t>
{
    if((from_base < static_cast<digit_t>(2)) || (to_base < static_cast<digit_t>(2))) {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if(digits.empty()) {
        throw std::invalid_argument("Input digit list may not be empty");
    }

    for(digit_t const d : digits) {
        if(d >= from_base) {
            throw std::invalid_argument("Digit out of range for input base");
        }
    }

    bool const is_zero =
        std::all_of(digits.cbegin(),
                    digits.cend(),
                    [](digit_t const d_val) { return d_val == static_cast<digit_t>(0); });

    if(is_zero) {
        return {static_cast<digit_t>(0)};
    }

    std::uint64_t value = static_cast<std::uint64_t>(0U);

    for(digit_t const d : digits) {
        value = ((value * static_cast<std::uint64_t>(from_base)) + static_cast<std::uint64_t>(d));
    }

    std::vector<digit_t> result{};

    while(value > static_cast<std::uint64_t>(0U)) {
        digit_t const remainder =
            static_cast<digit_t>(value % static_cast<std::uint64_t>(to_base));
        result.push_back(remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    std::reverse(result.begin(), result.end());

    return result;
}

}  // namespace detail
}  // namespace all_your_base
