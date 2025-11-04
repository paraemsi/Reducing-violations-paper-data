#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <cctype>

namespace parallel_letter_frequency {

std::map<char, std::uint64_t> frequency(const std::vector<std::string_view>& texts) {
    std::vector<std::map<char, std::uint64_t>> local_freqs(texts.size());
    std::transform(std::execution::par, texts.begin(), texts.end(), local_freqs.begin(), [](const std::string_view& text) {
        std::map<char, std::uint64_t> freq;
        for (char c : text) {
            char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            if (std::isalpha(static_cast<unsigned char>(lower))) {
                ++freq[lower];
            }
        }
        return freq;
    });
    std::map<char, std::uint64_t> total_freq;
    for (const auto& freq : local_freqs) {
        for (const auto& pair : freq) {
            total_freq[pair.first] += pair.second;
        }
    }
    return total_freq;
}

}
