#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <cstddef>
#include <type_traits>
#include <limits>
#include <stdexcept>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base,
                                   const std::vector<std::uint32_t>& digits,
                                   std::uint32_t output_base);

template <typename DigitT, typename BaseT>
inline std::vector<std::uint32_t> convert(BaseT input_base,
                                          const std::vector<DigitT>& digits,
                                          BaseT output_base)
{
    static_assert(std::is_integral<DigitT>::value, "Digits must be integral");
    static_assert(std::is_integral<BaseT>::value, "Base type must be integral");

    std::vector<std::uint32_t> d2;
    d2.reserve(digits.size());

    for (std::size_t i = 0U; (i < digits.size()); ++i) {
        const DigitT v = digits[i];
        if (v < static_cast<DigitT>(0)) {
            throw std::invalid_argument("digits must be non-negative");
        }
        using UnsignedDigitT = typename std::make_unsigned<DigitT>::type;
        const std::uint64_t vv =
            static_cast<std::uint64_t>(static_cast<UnsignedDigitT>(v));
        if (vv > static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max())) {
            throw std::invalid_argument("digit too large");
        }
        d2.push_back(static_cast<std::uint32_t>(vv));
    }

    if (input_base < static_cast<BaseT>(0)) {
        throw std::invalid_argument("base must be positive");
    }
    if (output_base < static_cast<BaseT>(0)) {
        throw std::invalid_argument("base must be positive");
    }

    using UnsignedBaseT = typename std::make_unsigned<BaseT>::type;
    const std::uint64_t inb =
        static_cast<std::uint64_t>(static_cast<UnsignedBaseT>(input_base));
    const std::uint64_t outb =
        static_cast<std::uint64_t>(static_cast<UnsignedBaseT>(output_base));

    if ((inb > static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max())) ||
        (outb > static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max()))) {
        throw std::invalid_argument("base too large");
    }

    return convert(static_cast<std::uint32_t>(inb),
                   d2,
                   static_cast<std::uint32_t>(outb));
}

}  // namespace all_your_base

#endif  // ALL_YOUR_BASE_H
