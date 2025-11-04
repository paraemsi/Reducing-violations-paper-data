#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, std::uint32_t>;

// The tests expect the function to be named 'frequency'
auto frequency(const std::vector<std::string>& texts) -> parallel_letter_frequency::frequency_map;

}

#endif

