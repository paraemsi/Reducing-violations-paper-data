#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

/**
 * Calculate letter frequency across the provided texts.
 *
 * The function is case-insensitive and counts only ASCII alphabetic
 * characters (A–Z / a–z). It may use multiple threads internally but
 * exposes a simple sequential interface.
 */
frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

