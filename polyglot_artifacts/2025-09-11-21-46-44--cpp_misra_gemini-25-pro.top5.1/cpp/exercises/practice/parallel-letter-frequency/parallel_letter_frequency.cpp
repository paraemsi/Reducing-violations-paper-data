#include "parallel_letter_frequency.h"

#include <cctype>
#include <cstdint>
#include <execution>
#include <locale>
#include <unordered_map>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

namespace parallel_letter_frequency {

using FreqMap = std::unordered_map<std::string, std::uint64_t>;

std::unordered_map<std::string, std::uint64_t>
frequency(const std::vector<std::string_view> &texts) {
  if (texts.empty()) {
    return {};
  }

  auto count_letters_in_string = [](const std::string_view &s) {
    FreqMap counts{};
    const std::locale loc{};
    for (char const c : s) {
      if (std::isalpha(c, loc)) {
        counts[std::string(1, std::tolower(c, loc))]++;
      }
    }
    return counts;
  };

  auto merge_maps = [](FreqMap a, const FreqMap &b) {
    for (const auto &pair : b) {
      a[pair.first] += pair.second;
    }
    return a;
  };

  return std::transform_reduce(std::execution::par, texts.cbegin(),
                               texts.cend(), FreqMap{}, merge_maps,
                               count_letters_in_string);
}

} // namespace parallel_letter_frequency
