#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>

namespace parallel_letter_frequency {

// Define an alias for a fixed-width integer type
using count_type = std::int32_t;

std::map<char, count_type> frequency(const std::vector<std::string>& texts);

}

#endif

