#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

// Count the frequency of letters (case-insensitive, ASCII letters) across all texts.
// Non-letter characters are ignored.
frequency_map frequency(const std::vector<std::string_view>& texts) noexcept;

}

#endif

