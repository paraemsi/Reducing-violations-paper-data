#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <string>
#include <vector>
#include <map>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts);

}

#endif

