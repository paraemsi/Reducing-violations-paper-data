#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <vector>
#include <cstddef>
#include <string_view>

namespace parallel_letter_frequency {

 // Calculate the frequency of letters [a-z] (case-insensitive) across all texts.
 // Non-letter characters are ignored.
 // This overload chooses a reasonable default number of worker threads.
 std::map<char, int> frequency(const std::vector<std::string_view>& texts);
 std::map<char, int> frequency(const std::vector<std::string>& texts);

 // Same as above, but allows the caller to specify the number of worker threads.
 // If workers == 0, a single worker is used.
 // The effective worker count will not exceed texts.size().
 std::map<char, int> frequency(const std::vector<std::string_view>& texts, std::size_t workers);
 std::map<char, int> frequency(const std::vector<std::string>& texts, std::size_t workers);

}

#endif

