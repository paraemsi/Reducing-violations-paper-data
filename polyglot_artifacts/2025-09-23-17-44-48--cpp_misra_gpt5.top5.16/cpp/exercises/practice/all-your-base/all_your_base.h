#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <type_traits>
#include <vector>

namespace all_your_base {

std::vector<std::uint32_t> convert(std::uint32_t input_base,
                                   const std::vector<std::uint32_t>& digits,
                                   std::uint32_t output_base);

template <typename T>
std::vector<T> convert(std::uint32_t input_base,
                       const std::vector<T>& digits,
                       std::uint32_t output_base)
{
    static_assert((std::is_integral<T>::value) && (std::is_unsigned<T>::value),
                  "T must be an unsigned integral type");

    std::vector<std::uint32_t> digits32{};
    digits32.reserve(digits.size());
    for (std::size_t i{0U}; i < digits.size(); ++i) {
        const std::uint64_t v64{static_cast<std::uint64_t>(digits[i])};
        if ((v64 > static_cast<std::uint64_t>(std::numeric_limits<std::uint32_t>::max()))) {
            throw std::overflow_error("digit does not fit in 32 bits");
        } else {
            // ok
        }
        digits32.push_back(static_cast<std::uint32_t>(v64));
    }

    const std::vector<std::uint32_t> out32{convert(input_base, digits32, output_base)};

    std::vector<T> out{};
    out.reserve(out32.size());
    for (std::size_t i{0U}; i < out32.size(); ++i) {
        const std::uint64_t v64{static_cast<std::uint64_t>(out32[i])};
        if ((v64 > static_cast<std::uint64_t>(std::numeric_limits<T>::max()))) {
            throw std::overflow_error("output digit does not fit in target type");
        } else {
            // ok
        }
        out.push_back(static_cast<T>(out32[i]));
    }

    return out;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
