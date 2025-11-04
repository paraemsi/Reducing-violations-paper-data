#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Map of lowercase letter -> count
using frequency_map = std::map<char, int>;

/*
 * Count case-insensitive ASCII letters [a-z] across all input texts in parallel.
 */
frequency_map frequency(const std::vector<std::string>& texts);

// Overload to accept string_view inputs (used by tests)
frequency_map frequency(const std::vector<std::string_view>& texts);

// Overload to accept const char* inputs as well.
frequency_map frequency(const std::vector<const char*>& texts);

}  // namespace parallel_letter_frequency

#endif

