#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <vector>
#include <string>
#include <cstdint>

namespace parallel_letter_frequency {

// The tests expect int, so we need to use int in the interface
// We'll use a fixed-width type internally and cast when necessary
using FrequencyMap = std::map<char, int>;
FrequencyMap frequency(const std::vector<std::string>& texts);

}

#endif

