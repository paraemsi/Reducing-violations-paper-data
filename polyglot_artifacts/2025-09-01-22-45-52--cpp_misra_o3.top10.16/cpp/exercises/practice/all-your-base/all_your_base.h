#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>
#include <stdexcept>
#include <type_traits>

namespace all_your_base {

/*  Convert a sequence of digits expressed in `from_base` into a sequence
 *  of digits expressed in `to_base`.
 *
 *  Both bases must be greater than, or equal to, 2.
 *  Each digit in the input sequence must be less than `from_base`.
 *
 *  On invalid input an `std::invalid_argument` exception is thrown.
 */
auto convert(const std::vector<std::uint32_t>& digits,
             std::uint32_t from_base,
             std::uint32_t to_base) -> std::vector<std::uint32_t>;

/*  Overload matching the parameter order used by the test suite:
 *      convert(from_base, digits, to_base)
 *  This simply forwards to the implementation that takes (digits, …).
 */
/*  Helper overload: parameter order (from_base, digits, to_base) used by the
 *  Exercism test-suite.  Defined `inline` in the header so it is always
 *  available to translation units that include this file.
 */
inline auto convert(std::uint32_t from_base,
                    const std::vector<std::uint32_t>& digits,
                    std::uint32_t to_base) -> std::vector<std::uint32_t>
{
    return convert(digits, from_base, to_base);
}

/*  Convenience overload for the exact signature used in the Exercism
 *  tests: bases are passed as ordinary `int` literals, while the digit
 *  container uses the non-fixed-width `unsigned int`.
 *
 *  The function validates the bases, forwards the work to the existing
 *  `convert` wrapper for `unsigned int`, and returns the result.
 */
inline auto convert(int from_base,
                    const std::vector<unsigned int>& digits,
                    int to_base) -> std::vector<unsigned int>
{
    if((from_base < 2) || (to_base < 2))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    /*  Promote bases to unsigned-int before calling the wrapper that
     *  operates entirely in that type.
     */
    const unsigned int u_from {static_cast<unsigned int>(from_base)};
    const unsigned int u_to   {static_cast<unsigned int>(to_base)};

    return convert(digits, u_from, u_to);
}

/*  Template wrapper to interoperate with client code that might use
 *  other integral types (e.g. the built-in `int`).  The wrapper
 *  converts its arguments to the fixed-width, unsigned implementation
 *  type, delegates the real work, then converts the result back.
 */
template<typename IntT,
         typename = std::enable_if_t<!std::is_same<IntT, std::uint32_t>::value>>
auto convert(const std::vector<IntT>& digits,
             IntT from_base,
             IntT to_base) -> std::vector<IntT>
{
    static_assert((std::is_integral<IntT>::value) && (!std::is_same<IntT, bool>::value),
                  "IntT must be a (non-bool) integral type");

    /*  Validate the bases and the input sequence before any type casting that
     *  could mask negative values.
     */
    if((from_base < static_cast<IntT>(2)) || (to_base < static_cast<IntT>(2)))
    {
        throw std::invalid_argument("Bases must be >= 2");
    }

    if(digits.empty())
    {
        throw std::invalid_argument("Input digit sequence may not be empty");
    }

    std::vector<std::uint32_t> wide_digits {};
    wide_digits.reserve(digits.size());

    for(const IntT d : digits)
    {
        if(((d < static_cast<IntT>(0)) || (d >= from_base)))
        {
            throw std::invalid_argument("Digit out of range for input base");
        }

        wide_digits.push_back(static_cast<std::uint32_t>(d));
    }

    const auto wide_result = convert(wide_digits,
                                     static_cast<std::uint32_t>(from_base),
                                     static_cast<std::uint32_t>(to_base));

    std::vector<IntT> result {};
    result.reserve(wide_result.size());

    for(const std::uint32_t d : wide_result)
    {
        result.push_back(static_cast<IntT>(d));
    }

    return result;
}

/*  Template overload with parameter order (from_base, digits, to_base)
 *  for non-std::uint32_t integral types.  It simply forwards to the
 *  existing (digits, from_base, to_base) wrapper.
 */
template<typename IntT,
         typename = std::enable_if_t<!std::is_same_v<IntT, std::uint32_t> &&
                                     std::is_integral_v<IntT> &&
                                     !std::is_same_v<IntT, bool>>>
auto convert(IntT from_base,
             const std::vector<IntT>& digits,
             IntT to_base) -> std::vector<IntT>
{
    return convert(digits, from_base, to_base);
}

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
