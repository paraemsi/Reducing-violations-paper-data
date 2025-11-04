#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>
#include <type_traits>
#include <cstddef>

namespace all_your_base {

 // Internal helper operating on 32-bit unsigned digits
std::vector<std::uint32_t> convert_u32(std::uint32_t in_base,
                                       const std::vector<std::uint32_t>& digits,
                                       std::uint32_t out_base) noexcept(false);

// Public template to adapt to caller's digit type without using standard integer type names
template <typename Digit>
std::vector<Digit> convert(std::uint32_t in_base,
                           const std::vector<Digit>& digits,
                           std::uint32_t out_base) noexcept(false) {
    static_assert(std::is_unsigned<Digit>::value, "Digit must be an unsigned integer type");
    static_assert(sizeof(Digit) == sizeof(std::uint32_t), "Digit must be 32 bits wide");

    std::vector<std::uint32_t> tmp;
    tmp.reserve(digits.size());
    for (std::size_t i = static_cast<std::size_t>(0); i < digits.size(); i = i + static_cast<std::size_t>(1)) {
        tmp.push_back(static_cast<std::uint32_t>(digits[i]));
    }

    const std::vector<std::uint32_t> out_u32 = convert_u32(in_base, tmp, out_base);

    std::vector<Digit> out;
    out.reserve(out_u32.size());
    for (std::size_t i = static_cast<std::size_t>(0); i < out_u32.size(); i = i + static_cast<std::size_t>(1)) {
        out.push_back(static_cast<Digit>(out_u32[i]));
    }
    return out;
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
