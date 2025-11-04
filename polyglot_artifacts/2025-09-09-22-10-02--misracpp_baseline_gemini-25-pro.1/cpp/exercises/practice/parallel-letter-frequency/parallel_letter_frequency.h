#pragma once

#include <map>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using letter_counts = std::map<char, int>;

letter_counts frequency(const std::vector<std::string_view> &texts);

} // namespace parallel_letter_frequency


