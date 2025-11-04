#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>
#include <cstdint>

namespace parallel_letter_frequency {

using counter_t = std::int32_t;  /* Underlying type name appears only inside alias per MISRA note */
using frequency_map = std::unordered_map<char, counter_t>;

frequency_map frequency(const std::vector<std::string_view>& texts);

}  /* namespace parallel_letter_frequency */

#endif

