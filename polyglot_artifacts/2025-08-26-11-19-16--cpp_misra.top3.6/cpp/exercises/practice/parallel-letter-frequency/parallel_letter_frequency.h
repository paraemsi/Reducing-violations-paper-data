#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

using text_t = std::string;
using frequency_map_t = std::map<char, std::uint32_t>;

/**
 * MISRA: Provide explicit inline namespace scope for function declaration
 * Exercism test suite expects the function to be named 'frequency'
 */
frequency_map_t frequency(const std::vector<parallel_letter_frequency::text_t>& texts);

} // namespace parallel_letter_frequency

#endif

