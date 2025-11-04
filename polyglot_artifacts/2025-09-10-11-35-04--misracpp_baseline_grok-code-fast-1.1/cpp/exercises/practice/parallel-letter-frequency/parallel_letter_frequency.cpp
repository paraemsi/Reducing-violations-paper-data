#include "parallel_letter_frequency.h"

#include <algorithm>
#include <execution>
#include <map>
#include <string>
#include <string_view>
#include <vector>
#include <cctype>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    auto count_letters = [](const std::string_view& text) -> std::map<char, int> {
        std::map<char, int> freq;
        for (char c : text) {
            if (std::isalpha(c)) {
                freq[std::tolower(c)]++;
            }
        }
        return freq;
    };

    auto combine_maps = [](std::map<char, int> a, std::map<char, int> b) -> std::map<char, int> {
        for (const auto& pair : b) {
            a[pair.first] += pair.second;
        }
        return a;
    };

    return std::transform_reduce(
        std::execution::par,
        texts.begin(),
        texts.end(),
        std::map<char, int>{},
        combine_maps,
        count_letters
    );
}

}
