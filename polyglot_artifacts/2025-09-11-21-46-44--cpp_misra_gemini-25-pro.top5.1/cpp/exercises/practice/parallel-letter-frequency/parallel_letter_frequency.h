#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <unordered_map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

std::unordered_map<std::string, std::uint64_t> frequency(const std::vector<std::string_view> &texts);

} // namespace parallel_letter_frequency

#endif

