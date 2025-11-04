#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, std::uint64_t> frequency(const std::vector<std::string_view>& texts);

}
