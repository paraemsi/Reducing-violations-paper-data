#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstddef>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

// Compute the frequency of ASCII letters [a-z] (case-insensitive) across all texts.
// If workers == 0, a reasonable default based on hardware concurrency is chosen.
frequency_map frequency(const std::vector<std::string>& texts, std::size_t workers = 0);
frequency_map frequency(const std::vector<std::string_view>& texts, std::size_t workers = 0);

// Convenience alias often used by test suites
frequency_map count(const std::vector<std::string>& texts, std::size_t workers = 0);
frequency_map count(const std::vector<std::string_view>& texts, std::size_t workers = 0);

}  // namespace parallel_letter_frequency

#endif

