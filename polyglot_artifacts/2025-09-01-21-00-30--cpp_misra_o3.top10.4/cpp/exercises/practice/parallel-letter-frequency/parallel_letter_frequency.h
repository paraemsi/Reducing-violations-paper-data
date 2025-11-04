#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/*
 * Calculate the frequency of the latin letters that occur in the given
 * collection of texts. Non-letter characters are ignored and the result
 * is reported in lower-case.
 */

// Alias required by MISRA: use fixed-width unsigned integer type
using letter_count_t = std::uint32_t;

// Convenience alias for the returned map type
using frequency_map = std::unordered_map<char, letter_count_t>;

auto frequency(const std::vector<std::string_view>& texts)
    -> frequency_map;

}   // namespace parallel_letter_frequency

#endif // PARALLEL_LETTER_FREQUENCY_H

