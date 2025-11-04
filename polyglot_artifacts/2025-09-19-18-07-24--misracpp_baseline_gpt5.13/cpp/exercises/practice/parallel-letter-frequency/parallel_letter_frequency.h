#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using frequency_map = std::map<char, int>;

[[nodiscard]] frequency_map frequency(const std::vector<std::string_view>& texts);
[[nodiscard]] frequency_map frequency(const std::vector<std::string>& texts);

}

#endif

