#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <cstdint>
#include <vector>

namespace all_your_base {

/**
 * \brief Convert a sequence of digits expressed in one base to a
 *        sequence of digits expressed in another base.
 *
 * \param[in]  in_base     The base of the input digit sequence (must be > 1).
 * \param[in]  in_digits   Most-significant-digit-first sequence in the
 *                         source base. An empty vector encodes the value 0.
 * \param[in]  out_base    The base for the resulting digit sequence (must be > 1).
 *
 * \return A most-significant-digit-first digit sequence in the requested base.
 *
 * \throws std::invalid_argument if any pre-condition is violated.
 */
auto convert(std::uint32_t in_base,
             std::vector<std::uint32_t> const& in_digits,
             std::uint32_t out_base) -> std::vector<std::uint32_t>;

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
