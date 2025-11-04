#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

/*
 * Count the frequency of each ASCII letter ('a'–'z', case-insensitive)
 * in the provided collection of texts. Non-alphabetic characters are ignored.
 *
 * The function is thread-safe and employs parallel processing internally.
 */
[[nodiscard]] frequency_map frequency(const std::vector<std::string>& texts);

}

#endif

