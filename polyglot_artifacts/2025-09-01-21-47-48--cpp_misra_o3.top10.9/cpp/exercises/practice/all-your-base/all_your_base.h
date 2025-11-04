#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>
#include <cstdint>

namespace all_your_base {

using digit_t = std::uint32_t;
using base_t  = std::uint32_t;

/* Convert the number represented by `digits`, given its current
 * radix `from_base`, into the corresponding digit sequence in
 * the new radix `to_base`.
 *
 * \param from_base  The base in which the incoming digit sequence is expressed.
 * \param digits     The digit sequence (most–significant digit first).
 * \param to_base    The desired target base for the output sequence.
 *
 * Any invalid input (illegal base, empty vector, leading zeros,
 * or digit ≥ from_base) results in std::invalid_argument.
 */
auto convert(base_t from_base,
             const std::vector<digit_t>& digits,
             base_t to_base) -> std::vector<digit_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
