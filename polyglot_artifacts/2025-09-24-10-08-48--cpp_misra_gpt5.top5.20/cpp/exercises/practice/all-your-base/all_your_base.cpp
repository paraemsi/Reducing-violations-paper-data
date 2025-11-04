#include "all_your_base.h"

#include <algorithm>
#include <cstdint>
#include <stdexcept>
#include <vector>

namespace all_your_base {

using u32 = std::uint32_t;
using Digits = std::vector<u32>;

static Digits convert_impl(const u32 in_base, const Digits& in_digits, const u32 out_base)
{
    if ((in_base < static_cast<u32>(2U)) || (out_base < static_cast<u32>(2U)))
    {
        throw std::invalid_argument("base must be >= 2");
    }

    if (in_digits.empty())
    {
        return Digits{};
    }

    // Skip leading zeros
    std::size_t first_non_zero = 0U;
    while ((first_non_zero < in_digits.size()) && (in_digits[first_non_zero] == static_cast<u32>(0U)))
    {
        first_non_zero = first_non_zero + 1U;
    }

    if (first_non_zero == in_digits.size())
    {
        return Digits{};
    }

    // Validate digits
    for (std::size_t i = first_non_zero; i < in_digits.size(); i = i + 1U)
    {
        if (in_digits[i] >= in_base)
        {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    // Convert input digits to an integer value
    using u64 = std::uint64_t;
    u64 value = static_cast<u64>(0U);
    for (std::size_t i = first_non_zero; i < in_digits.size(); i = i + 1U)
    {
        value = (value * static_cast<u64>(in_base)) + static_cast<u64>(in_digits[i]);
    }

    // Convert integer value to output base digits
    Digits out{};
    if (value == static_cast<u64>(0U))
    {
        // zero value yields empty digit sequence per spec/tests
    }
    else
    {
        while (value > static_cast<u64>(0U))
        {
            const u32 remainder = static_cast<u32>(value % static_cast<u64>(out_base));
            out.push_back(remainder);
            value = value / static_cast<u64>(out_base);
        }
        std::reverse(out.begin(), out.end());
    }

    return out;
}

std::vector<unsigned int> convert(const unsigned int in_base_ui, const std::vector<unsigned int>& in_digits_ui, const unsigned int out_base_ui)
{
    // Adapt external unsigned int API to fixed-width internal implementation.
    const u32 in_base = static_cast<u32>(in_base_ui);
    const u32 out_base = static_cast<u32>(out_base_ui);

    Digits in_digits{};
    in_digits.reserve(in_digits_ui.size());
    for (std::size_t i = 0U; i < in_digits_ui.size(); i = i + 1U)
    {
        in_digits.push_back(static_cast<u32>(in_digits_ui[i]));
    }

    const Digits out_digits = convert_impl(in_base, in_digits, out_base);

    std::vector<unsigned int> result{};
    result.reserve(out_digits.size());
    for (std::size_t i = 0U; i < out_digits.size(); i = i + 1U)
    {
        result.push_back(static_cast<unsigned int>(out_digits[i]));
    }

    return result;
}

}  // namespace all_your_base
