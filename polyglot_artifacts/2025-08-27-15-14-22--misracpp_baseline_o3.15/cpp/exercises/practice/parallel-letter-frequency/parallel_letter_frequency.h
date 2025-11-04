#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

// Calculate the frequency of letters (case-insensitive a-z) present in the
// given list of texts. Non-alphabetic characters are ignored. The workload is
// automatically distributed over several threads.
frequency_map frequency(const std::vector<std::string_view>& texts);

}  // namespace parallel_letter_frequency

#endif

