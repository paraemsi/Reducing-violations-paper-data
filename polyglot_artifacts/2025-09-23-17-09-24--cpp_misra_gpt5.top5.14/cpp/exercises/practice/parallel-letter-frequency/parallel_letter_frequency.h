#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <locale>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

struct char_compare final {
    bool operator()(const char lhs, const char rhs) const noexcept
    {
        const auto li = std::char_traits<char>::to_int_type(lhs);
        const auto ri = std::char_traits<char>::to_int_type(rhs);
        return (li < ri);
    }
};

using frequency_map = std::map<char, std::int32_t, char_compare>;

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;
auto frequency(const std::vector<std::string>& texts) -> frequency_map;

}  // namespace parallel_letter_frequency

#endif

