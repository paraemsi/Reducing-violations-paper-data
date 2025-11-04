#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <string>
#include <string_view>
#include <map>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

frequency_map frequency(const std::vector<std::string>& texts);
frequency_map frequency(const std::vector<std::string_view>& texts);

}

#endif

