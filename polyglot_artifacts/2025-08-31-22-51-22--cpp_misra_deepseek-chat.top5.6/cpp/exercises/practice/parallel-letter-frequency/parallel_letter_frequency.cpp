#include "parallel_letter_frequency.h"
#include <execution>
#include <algorithm>
#include <map>
#include <cctype>
#include <functional>
#include <numeric>
#include <vector>
#include <string>
#include <array>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) {
        return {};
    }
    
    // Use an array of 26 integers to count frequencies for 'a' to 'z'
    // This is more efficient for reduction
    constexpr std::int32_t num_letters = 26;
    std::array<std::int32_t, num_letters> result_array = std::transform_reduce(
        std::execution::par,
        texts.begin(), texts.end(),
        std::array<std::int32_t, num_letters>{}, // Start with all zeros
        // Binary operation to reduce two arrays
        [](std::array<std::int32_t, num_letters> lhs, const std::array<std::int32_t, num_letters>& rhs) -> std::array<std::int32_t, num_letters> {
            for (std::int32_t i = 0; i < num_letters; ++i) {
                lhs[i] += rhs[i];
            }
            return lhs;
        },
        // Unary operation to count letters in each text
        [](const std::string& text) -> std::array<std::int32_t, num_letters> {
            std::array<std::int32_t, num_letters> local_counts{};
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase and count
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    local_counts[static_cast<std::int32_t>(lower_c - 'a')]++;
                }
            }
            return local_counts;
        }
    );
    
    // Convert the array to a map
    std::map<char, int> result;
    for (std::int32_t i = 0; i < num_letters; ++i) {
        if (result_array[i] > 0) {
            result[static_cast<char>('a' + i)] = result_array[i];
        }
    }
    return result;
}

}
