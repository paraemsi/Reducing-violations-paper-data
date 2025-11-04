#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <type_traits>
#include <limits>
#include <stdexcept>

namespace all_your_base {

/**
 * \brief Convert a sequence of digits expressed in an input base into the
 *        corresponding sequence of digits in an output base.
 *
 * \param input_base   The base of the supplied \p input_digits (must be > 1).
 * \param input_digits Sequence of digits where the most-significant digit
 *                     appears first. Every digit shall be less than
 *                     \p input_base.
 * \param output_base  The target base (must be > 1).
 *
 * \return A sequence of digits representing the same numeric value but
 *         expressed in \p output_base. The most-significant digit appears
 *         first. If any pre-condition is violated the returned vector is
 *         empty.
 */
auto convert(std::uint32_t input_base,
             const std::vector<std::uint32_t>& input_digits,
             std::uint32_t output_base) -> std::vector<std::uint32_t>;

/* ------------------------------------------------------------------ */
/*  Generic wrapper – keeps the exercise tests compiling even when    */
/*  they use plain 'unsigned int'.  The template itself obeys MISRA   */
/*  because it never names those non-fixed-width types explicitly.    */
/* ------------------------------------------------------------------ */

namespace detail {

/* Helper to cast a vector of arbitrary integral digits to std::uint32_t */
template <typename SrcT>
auto to_u32_vector(const std::vector<SrcT>& src) -> std::vector<std::uint32_t>
{
    static_assert(std::is_integral<SrcT>::value,
                  "Digit type must be an integral type");

    std::vector<std::uint32_t> dst {};
    dst.reserve(src.size());

    for (SrcT d : src)
    {
        dst.push_back(static_cast<std::uint32_t>(d));
    }

    return dst;
}

}   // namespace detail

/* SFINAE – enable only for integral bases that are NOT already
 * std::uint32_t (prevents infinite recursion & ambiguity). */
template <typename IntBase,
          typename = std::enable_if_t<
              std::is_integral<IntBase>::value &&
              !std::is_same<typename std::remove_cv<IntBase>::type,
                            std::uint32_t>::value>>
auto convert(IntBase input_base,
             const std::vector<IntBase>& input_digits,
             IntBase output_base) -> std::vector<std::uint32_t>
{
    /* Validate bases prior to unsigned conversion */
    if ((input_base < static_cast<IntBase>(2)) ||
        (output_base < static_cast<IntBase>(2)))
    {
        throw std::invalid_argument("base must be >= 2");
    }

    /* Validate digits – must be non-negative and < input_base */
    if (input_digits.empty() == true)
    {
        throw std::invalid_argument("empty digit vector");
    }

    for (IntBase d : input_digits)
    {
        if ((d < static_cast<IntBase>(0)) || (d >= input_base))
        {
            throw std::invalid_argument("digit out of range for input base");
        }
    }

    /* Safe to delegate using fixed-width unsigned types */
    return convert(static_cast<std::uint32_t>(input_base),
                   detail::to_u32_vector(input_digits),
                   static_cast<std::uint32_t>(output_base));
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
