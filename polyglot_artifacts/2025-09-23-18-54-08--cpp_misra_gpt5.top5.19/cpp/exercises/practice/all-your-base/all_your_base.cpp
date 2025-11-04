#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>

namespace all_your_base {

auto convert(std::uint32_t in_base, const digits_t& digits, std::uint32_t out_base) -> digits_t
{
    if ((in_base < static_cast<std::uint32_t>(2U)) || (out_base < static_cast<std::uint32_t>(2U))) {
        throw std::invalid_argument("base must be >= 2");
    }

    if (digits.empty()) {
        return digits_t{};
    }

    for (std::size_t i = static_cast<std::size_t>(0U); i < digits.size(); ++i) {
        if (digits.at(i) >= in_base) {
            throw std::invalid_argument("invalid digit for input base");
        }
    }

    std::size_t first_non_zero = static_cast<std::size_t>(0U);
    while ((first_non_zero < digits.size()) && (digits.at(first_non_zero) == static_cast<digits_t::value_type>(0U))) {
        ++first_non_zero;
    }

    if (first_non_zero == digits.size()) {
        return digits_t{static_cast<digits_t::value_type>(0U)};
    }

    std::uint64_t acc = static_cast<std::uint64_t>(0U);
    for (std::size_t i = first_non_zero; i < digits.size(); ++i) {
        acc = (acc * static_cast<std::uint64_t>(in_base)) + static_cast<std::uint64_t>(digits.at(i));
    }

    digits_t out{};
    while (acc > static_cast<std::uint64_t>(0U)) {
        std::uint64_t rem64 = acc % static_cast<std::uint64_t>(out_base);
        out.push_back(static_cast<digits_t::value_type>(rem64));
        acc = acc / static_cast<std::uint64_t>(out_base);
    }

    std::reverse(out.begin(), out.end());
    return out;
}

}  // namespace all_your_base
