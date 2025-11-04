#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

/*  Calculate the frequency of each alphabetic character (case–insensitive)
    in the supplied list of texts. The work is split across several threads
    (at most one per hardware core, never more than the number of input
    strings) and merged once all threads have finished.
*/
frequency_map letter_frequency(const std::vector<std::string>& texts);

/*  Exercism tests expect the public entry point to be named `frequency`.
    Provide a thin wrapper that forwards to `letter_frequency` to keep the
    existing implementation unchanged. */
frequency_map frequency(const std::vector<std::string>& texts);

}

#endif

