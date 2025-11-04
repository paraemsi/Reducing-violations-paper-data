#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <type_traits>

namespace all_your_base {

auto convert(const std::vector<std::uint32_t>& digits,
             std::uint32_t from_base,
             std::uint32_t to_base) -> std::vector<std::uint32_t>;

template <typename DigitT>
auto convert(std::uint32_t from_base,
             const std::vector<DigitT>& digits,
             std::uint32_t to_base) -> std::vector<DigitT>
{
    static_assert(std::is_integral<DigitT>::value,
                  "Digit type must be integral");
    static_assert(std::is_unsigned<DigitT>::value,
                  "Digit type must be unsigned");

    std::vector<std::uint32_t> digits32{};
    digits32.reserve(digits.size());

    for(const DigitT d : digits)
    {
        digits32.push_back(static_cast<std::uint32_t>(d));
    }

    const std::vector<std::uint32_t> converted32 =
        all_your_base::convert(digits32, from_base, to_base);

    std::vector<DigitT> result{};
    result.reserve(converted32.size());

    for(const std::uint32_t d : converted32)
    {
        result.push_back(static_cast<DigitT>(d));
    }

    return result;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
