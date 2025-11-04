#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

/* Count the frequency of ASCII letters (case-insensitive) across all input texts.
 * Non-letter characters are ignored. Keys in the returned map are lowercase 'a'-'z'.
 */
frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

