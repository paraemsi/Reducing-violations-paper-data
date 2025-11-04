#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <cstdint>
#include <map>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using char_type = std::string_view::value_type;

struct char_less final
{
    auto operator()(const char_type lhs, const char_type rhs) const noexcept -> bool
    {
        return std::char_traits<char_type>::lt(lhs, rhs);
    }
};

using frequency_map = std::map<char_type, std::uint32_t, char_less>;

auto frequency(const std::vector<std::string>& texts) -> frequency_map;
auto frequency(const std::vector<std::string_view>& texts) -> frequency_map;

}

#endif

