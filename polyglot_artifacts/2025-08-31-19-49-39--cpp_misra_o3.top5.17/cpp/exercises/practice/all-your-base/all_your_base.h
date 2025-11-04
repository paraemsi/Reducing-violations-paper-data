#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>
#include <type_traits>
#include <stdexcept>
#include <limits>

namespace all_your_base {

using digit_t = std::uint32_t;

/**
 * \brief Convert a sequence of digits from one base to another.
 *
 * \param[in] digits     The input digits, most-significant first.
 * \param[in] from_base  The base of the input digits (>= 2).
 * \param[in] to_base    The base for the output digits (>= 2).
 *
 * \return A vector of digits representing the same value in \p to_base.
 *
 * \throw std::invalid_argument if either base is < 2, the digit list is
 *        empty, or any digit is not valid for \p from_base.
 */
namespace detail {
auto convert_impl(digit_t                     from_base,
                  std::vector<digit_t> const& digits,
                  digit_t                     to_base) -> std::vector<digit_t>;
}  // namespace detail

template <typename InputDigitT>
auto convert(digit_t                     from_base,
             std::vector<InputDigitT> const& digits,
             digit_t                     to_base) -> std::vector<digit_t>
{
    static_assert(std::is_integral<InputDigitT>::value, "Digit type must be integral");

    std::vector<digit_t> normalized_digits{};
    normalized_digits.reserve(digits.size());

    for(InputDigitT const d : digits) {
        if constexpr (std::numeric_limits<InputDigitT>::is_signed) {
            if(d < static_cast<InputDigitT>(0)) {
                throw std::invalid_argument("Negative digit not allowed");
            }
        }
        normalized_digits.push_back(static_cast<digit_t>(d));
    }

    return detail::convert_impl(from_base, normalized_digits, to_base);
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
