#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstddef>
#include <map>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, std::size_t>;

/* Count the frequency of letters (a-z, case-insensitive) across all input texts. */
frequency_map frequency(const std::vector<std::string_view>& texts);

}  // namespace parallel_letter_frequency

#endif

