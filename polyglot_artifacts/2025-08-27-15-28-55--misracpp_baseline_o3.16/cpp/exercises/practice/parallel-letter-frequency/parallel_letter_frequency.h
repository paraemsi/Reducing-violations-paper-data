#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

    // Return the total frequency of each ASCII alphabetic letter
    // (case-insensitive) found in the supplied texts.
    std::map<char, int> frequency(const std::vector<std::string>& texts);
    std::map<char, int> frequency(const std::vector<std::string_view>& texts);

}

#endif

