#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

// Count the frequency of ASCII letters (A-Z, a-z) in the given texts.
// Case-insensitive: 'A' and 'a' are counted together as 'a'.
// Non-letter characters are ignored.
// The function employs parallelism across the input texts.
frequency_map frequency(const std::vector<std::string_view>& texts);
inline frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}

#endif

