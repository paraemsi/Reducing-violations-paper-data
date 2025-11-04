#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Count the frequency of each alphabetical character (case-insensitive)
using frequency_map = std::map<char, int>;
// across all supplied texts. Non-alphabet characters are ignored.
[[nodiscard]] frequency_map frequency(const std::vector<std::string_view>& texts);

}  // namespace parallel_letter_frequency

#endif // PARALLEL_LETTER_FREQUENCY_H

