#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

using letter_frequency_map = std::map<char, std::uint32_t>;

letter_frequency_map letter_frequency(const std::vector<std::string>& texts);

// Alias for backward compatibility with test suite
inline letter_frequency_map frequency(const std::vector<std::string>& texts)
{
    return letter_frequency(texts);
}

}

#endif

