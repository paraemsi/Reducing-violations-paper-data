#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <unordered_map>
#include <string>
#include <vector>
#include <cstdint>

namespace parallel_letter_frequency {

/* map 'a'-'z' → occurrence count */
using frequency_map = std::unordered_map<char, std::uint32_t>;

/* calculate the letter frequency of the supplied texts in parallel */
frequency_map frequency(const std::vector<std::string>& texts);

}

#endif

