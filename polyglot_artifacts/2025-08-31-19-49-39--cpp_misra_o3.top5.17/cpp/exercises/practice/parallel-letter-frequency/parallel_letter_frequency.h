#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <array>
#include <cstdint>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

// Alias for the result container
using frequency_map = std::unordered_map<char, std::uint32_t>;

/*
 * Calculate the frequency of the letters a-z (case–insensitive)
 * appearing in the supplied texts.
 *
 * Parallel execution is employed; the function is thread-safe.
 */
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}   // namespace parallel_letter_frequency

#endif   // PARALLEL_LETTER_FREQUENCY_H

