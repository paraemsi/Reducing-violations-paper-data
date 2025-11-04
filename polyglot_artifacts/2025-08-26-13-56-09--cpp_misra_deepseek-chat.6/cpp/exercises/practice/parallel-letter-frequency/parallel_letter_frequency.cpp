#include "parallel_letter_frequency.h"
#include <execution>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <cctype>
#include <functional>
#include <numeric>
#include <array>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Use a fixed-size array for 26 letters
    // Process each text to fill an array, then reduce them
    constexpr std::int32_t num_letters = 26;
    
    // Transform each text into an array of counts
    std::vector<std::array<std::int32_t, num_letters>> per_text_counts(texts.size());
    
    // Process each text in parallel
    std::transform(std::execution::par, texts.begin(), texts.end(), per_text_counts.begin(),
        [](const std::string& text) {
            std::array<std::int32_t, num_letters> counts{};
            for (unsigned char c : text) {
                if (std::isalpha(c)) {
                    // Convert to lowercase and index
                    char lower_c = std::tolower(c);
                    counts[static_cast<std::int32_t>(lower_c - 'a')]++;
                }
            }
            return counts;
        });
    
    // Reduce all arrays into one
    if (per_text_counts.empty()) {
        return {};
    }
    
    std::array<std::int32_t, num_letters> total_counts = std::reduce(
        std::execution::par,
        per_text_counts.begin() + 1, per_text_counts.end(),
        per_text_counts.front(),
        [](const std::array<std::int32_t, num_letters>& a, const std::array<std::int32_t, num_letters>& b) {
            std::array<std::int32_t, num_letters> result;
            for (std::int32_t i = 0; i < num_letters; i++) {
                result[i] = a[i] + b[i];
            }
            return result;
        });
    
    // Convert to the required map
    std::map<char, int> result;
    for (std::int32_t i = 0; i < num_letters; i++) {
        if (total_counts[i] > 0) {
            // The map value type is int, which may be different from int32_t
            // But since the function signature uses int, we need to cast
            result[static_cast<char>('a' + i)] = static_cast<int>(total_counts[i]);
        }
    }
    return result;
}

}
