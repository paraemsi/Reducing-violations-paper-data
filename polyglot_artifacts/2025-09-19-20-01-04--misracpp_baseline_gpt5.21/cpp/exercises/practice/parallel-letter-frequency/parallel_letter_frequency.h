#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>
#include <string_view>
#include <initializer_list>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

// Count the frequency of letters (ASCII, case-insensitive) across all input texts.
// Non-letter characters are ignored.
frequency_map frequency(const std::vector<std::string_view>& texts);
frequency_map frequency(const std::vector<std::string>& texts);
frequency_map frequency(std::initializer_list<std::string_view> texts);

}

#endif

