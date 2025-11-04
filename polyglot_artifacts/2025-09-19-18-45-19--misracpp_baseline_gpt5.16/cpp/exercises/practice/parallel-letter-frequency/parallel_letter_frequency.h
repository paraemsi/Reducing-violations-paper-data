#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

/* Map from lowercase ASCII letter to its frequency count. */
using frequency_map = std::map<char, int>;

// Compute aggregated letter frequency across all texts.
// Returns counts for letters 'a'..'z', case-insensitive.
[[nodiscard]] frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

