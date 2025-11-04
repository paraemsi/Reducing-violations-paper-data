#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

// Compute the total frequency of each ASCII alphabetic letter
// (case–insensitive) appearing in the given collection of texts.
// The work is distributed among several threads to exploit parallelism.
[[nodiscard]] std::map<char, int> frequency(const std::vector<std::string>& texts);
[[nodiscard]] std::map<char, int> frequency(const std::vector<std::string_view>& texts);

}

#endif

