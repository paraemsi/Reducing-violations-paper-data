#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstddef> // for std::size_t
#include <map>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Return a map with the case-insensitive frequency of every ASCII letter
// found in the supplied collection of input strings. The work is processed
// in parallel - one thread per input string - but the public interface
// remains entirely synchronous.
std::map<char, int> frequency(const std::vector<std::string_view>& input_strings,
                              std::size_t max_workers = 1);

} // namespace parallel_letter_frequency

#endif // PARALLEL_LETTER_FREQUENCY_H

