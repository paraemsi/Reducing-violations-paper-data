#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <cstddef>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

[[nodiscard]] auto frequency(const std::vector<std::string_view>& texts) -> std::map<char, std::uint32_t>;
[[nodiscard]] auto frequency(const std::vector<std::string>& texts) -> std::map<char, std::uint32_t>;

}

#endif

