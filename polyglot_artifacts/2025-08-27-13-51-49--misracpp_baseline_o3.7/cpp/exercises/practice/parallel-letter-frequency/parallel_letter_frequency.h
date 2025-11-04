#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

    // Count the frequency of letters in the given texts using parallel computation.
    // The returned map contains lowercase alphabetic characters ('a'-'z') as keys.
    std::map<char, int> frequency(const std::vector<std::string_view>& strings);

}

#endif

