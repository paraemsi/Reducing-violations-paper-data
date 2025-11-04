#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace all_your_base {

/*
 * Convert the number represented by `digits` interpreted in `from_base`
 * into its representation in `to_base`.
 * Throws std::invalid_argument if either base is < 2 or a digit is
 * not valid for the source base.
 */
namespace detail {

auto convert_core(std::int32_t from_base,
                  const std::vector<std::uint32_t>& digits,
                  std::int32_t to_base) -> std::vector<std::uint32_t>;

}  // namespace detail

template<typename UInt>
auto convert(std::int32_t from_base,
             const std::vector<UInt>& digits,
             std::int32_t to_base) -> std::vector<UInt>
{
    static_assert(std::is_unsigned_v<UInt>,
                  "Digits must be an unsigned integral type");
    static_assert(sizeof(UInt) <= sizeof(std::uint32_t),
                  "Digit type wider than 32 bits is not supported");

    std::vector<std::uint32_t> temp_digits {};
    temp_digits.reserve(digits.size());
    for(UInt d : digits)
    {
        temp_digits.push_back(static_cast<std::uint32_t>(d));
    }

    std::vector<std::uint32_t> temp_result =
        detail::convert_core(from_base, temp_digits, to_base);

    std::vector<UInt> result {};
    result.reserve(temp_result.size());
    for(std::uint32_t d : temp_result)
    {
        result.push_back(static_cast<UInt>(d));
    }

    return result;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
