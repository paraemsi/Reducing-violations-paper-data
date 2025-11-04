#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <string>
#include <map>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

// Count letters across all strings in texts, case-insensitive (ASCII A-Z).
// Non-letter characters are ignored. Uses parallel processing internally.
frequency_map frequency(const std::vector<std::string_view>& texts);
frequency_map frequency(const std::vector<std::string>& texts);

}

#endif

