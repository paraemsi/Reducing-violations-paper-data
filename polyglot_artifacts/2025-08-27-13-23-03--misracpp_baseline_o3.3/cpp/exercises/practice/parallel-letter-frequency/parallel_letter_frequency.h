#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

/*  Calculate the total frequency of each ASCII letter (case-insensitive)
    appearing in the provided texts. Non-letter characters are ignored.

    The function is thread-safe and employs a simple thread-pool strategy
    sized to hardware_concurrency() to speed up the computation.
*/
frequency_map frequency(const std::vector<std::string_view>& texts);
frequency_map frequency(const std::vector<std::string>& texts);

}  // namespace parallel_letter_frequency

#endif

