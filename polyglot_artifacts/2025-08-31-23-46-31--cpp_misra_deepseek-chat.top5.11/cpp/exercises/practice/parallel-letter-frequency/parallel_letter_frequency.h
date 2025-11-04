#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>

namespace parallel_letter_frequency {

using frequency_t = std::int_fast32_t;
using char_t = char;
std::map<char_t, frequency_t> frequency(const std::vector<std::string>& texts);

}

#endif

