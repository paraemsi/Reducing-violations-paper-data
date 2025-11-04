#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {


// Compute the letter frequency (case-insensitive, ASCII a-z) across all texts in parallel.
std::map<char, int> frequency(const std::vector<std::string_view>& texts);
std::map<char, int> frequency(const std::vector<std::string>& texts);

}

#endif

