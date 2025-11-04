#include "all_your_base.h"

namespace all_your_base {

namespace detail {

auto convert_core(std::int32_t from_base,
                  const std::vector<std::uint32_t>& digits,
                  std::int32_t to_base) -> std::vector<std::uint32_t>
{
    if((from_base < static_cast<std::int32_t>(2)) || (to_base < static_cast<std::int32_t>(2)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if(digits.empty())
    {
        return {static_cast<std::uint32_t>(0U)};
    }

    for(std::uint32_t digit : digits)
    {
        if(digit >= static_cast<std::uint32_t>(from_base))
        {
            throw std::invalid_argument("Digit out of range for source base");
        }
    }

    std::uint64_t value = static_cast<std::uint64_t>(0U);
    for(std::uint32_t digit : digits)
    {
        value = (value * static_cast<std::uint64_t>(from_base)) +
                static_cast<std::uint64_t>(digit);
    }

    std::vector<std::uint32_t> result {};
    if(value == static_cast<std::uint64_t>(0U))
    {
        result.push_back(static_cast<std::uint32_t>(0U));
        return result;
    }

    while(value > static_cast<std::uint64_t>(0U))
    {
        std::uint32_t remainder =
            static_cast<std::uint32_t>(value % static_cast<std::uint64_t>(to_base));
        result.insert(result.begin(), remainder);
        value = value / static_cast<std::uint64_t>(to_base);
    }

    return result;
}

}  // namespace detail
}  // namespace all_your_base
