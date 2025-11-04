#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

/* Calculate the total frequency of each letter (case-insensitive, a-z only)
 * across all provided texts, using parallel computation where beneficial.
 */
frequency_map frequency(const std::vector<std::string_view>& texts);
frequency_map frequency(const std::vector<std::string>& texts);

}  // namespace parallel_letter_frequency

#endif

