#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Return a map with the frequency of each ASCII letter (case-insensitive)
// found in the supplied texts. All non-alphabetic characters are ignored.
// The computation is performed in parallel where it makes sense.
std::map<char, int> frequency(const std::vector<std::string_view>& texts);

}  // namespace parallel_letter_frequency

#endif  // PARALLEL_LETTER_FREQUENCY_H

