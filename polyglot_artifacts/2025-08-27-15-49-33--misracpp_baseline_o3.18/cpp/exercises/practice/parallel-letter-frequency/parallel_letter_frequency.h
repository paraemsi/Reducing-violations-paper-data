#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H
#include <map>
#include <string>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

    // Count the frequency of ASCII letters in a collection of texts.
    // Non-alphabetic characters are ignored and letters are treated case-insensitively.

    // Preferred overload working with string_view (used by the tests)
    std::map<char, int> frequency(const std::vector<std::string_view>& texts);

    // Convenience overload accepting std::string.  It simply forwards to the
    // string_view version so either container type can be passed.
    std::map<char, int> frequency(const std::vector<std::string>& texts);

}

#endif

