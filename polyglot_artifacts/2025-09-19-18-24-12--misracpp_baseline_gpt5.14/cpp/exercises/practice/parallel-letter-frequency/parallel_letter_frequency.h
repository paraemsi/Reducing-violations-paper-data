#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

// Compute the total frequency of letters (a-z) across all texts, case-insensitive.
// Non-letter characters are ignored.
frequency_map frequency(const std::vector<std::string_view>& texts);
frequency_map frequency(const std::vector<std::string>& texts);

}  // namespace parallel_letter_frequency

#endif

