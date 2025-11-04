#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

    // Calculate the frequency of each ASCII letter (case–insensitive) appearing
    // in the supplied texts.  Non-alphabetic characters are ignored.
    //
    // The algorithm employs parallel tasks where each input string is processed
    // independently, then their results are merged.
    std::map<char, int> frequency(const std::vector<std::string_view>& texts);
    // Convenience overload for callers that have std::string containers.
    std::map<char, int> frequency(const std::vector<std::string>& texts);

}

#endif

