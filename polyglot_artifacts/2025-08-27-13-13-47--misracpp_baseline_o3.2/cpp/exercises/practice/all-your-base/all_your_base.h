#if !defined(ALL_YOUR_BASE_H)
#define ALL_YOUR_BASE_H

#include <vector>

namespace all_your_base {

/*
 * Convert a sequence of digits represented in `input_base` to the
 * corresponding sequence of digits in `output_base`.
 *
 * Parameters
 * ----------
 * input_base   : the base in which `input_digits` are expressed (≥ 2)
 * input_digits : the digits to convert, most-significant first
 * output_base  : the base for the returned digit sequence (≥ 2)
 *
 * The function throws std::invalid_argument when:
 *   • either base is < 2
 *   • the input digit list is empty
 *   • a digit is ≥ input_base
 */
std::vector<unsigned int> convert(unsigned int input_base,
                                  const std::vector<unsigned int>& input_digits,
                                  unsigned int output_base);

}  // namespace all_your_base

#endif // ALL_YOUR_BASE_H
