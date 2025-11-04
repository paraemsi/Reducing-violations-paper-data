#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

/*
 * Calculate the frequency of each alphabetic character (case-insensitive)
 * occurring in the provided texts.
 *
 * Only letters ‘a’–‘z’ are counted.  The returned map contains an entry
 * for every letter that appears at least once.
 */
frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

