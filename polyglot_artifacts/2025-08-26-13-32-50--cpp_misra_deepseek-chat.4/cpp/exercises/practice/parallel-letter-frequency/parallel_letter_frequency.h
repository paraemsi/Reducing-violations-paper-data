#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>

namespace parallel_letter_frequency {

// Define an alias that matches what the tests expect
using result_int_t = int;

std::map<char, result_int_t> frequency(const std::vector<std::string>& texts);

}

#endif

