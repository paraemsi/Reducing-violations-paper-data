#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstddef>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Frequency map type: counts for letters 'a'..'z' (case-insensitive), only present letters included.
using frequency_map = std::map<char, int>;

/**
 * Compute letter frequencies across all texts, optionally specifying the number of threads.
 * If threads == 0, a hardware-based default is used. The function clamps the thread
 * count to at most texts.size() and at least 1.
 */
frequency_map frequency(const std::vector<std::string_view>& texts, std::size_t threads = 0);

}  // namespace parallel_letter_frequency

#endif

