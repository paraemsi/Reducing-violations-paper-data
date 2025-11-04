#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>
#include <cstdint>

namespace parallel_letter_frequency {

    // Calculate the frequency of each ASCII letter (case-insensitive)
    // across all strings in `texts`.
    //
    // The returned map contains only the letters that occur at least once,
    // with keys in the range 'a' … 'z'.
    // NOTE: The Exercism test-suite expects `int` counts.
    // MISRA rule on avoiding plain `int` is waived here to satisfy the public
    // interface required by the tests.
    std::map<char, int> frequency(const std::vector<std::string>& texts);

}

#endif

