#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <cstdint>
#include <array>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) {
        return std::map<char, std::int32_t>();
    }
    
    // Create a mapping from uppercase to lowercase letters using character literals only
    // Since we can't use numerical values, we'll list all mappings explicitly
    constexpr std::array<std::pair<char, char>, 26> upper_to_lower = {{
        {'A', 'a'}, {'B', 'b'}, {'C', 'c'}, {'D', 'd'}, {'E', 'e'}, {'F', 'f'}, {'G', 'g'},
        {'H', 'h'}, {'I', 'i'}, {'J', 'j'}, {'K', 'k'}, {'L', 'l'}, {'M', 'm'}, {'N', 'n'},
        {'O', 'o'}, {'P', 'p'}, {'Q', 'q'}, {'R', 'r'}, {'S', 's'}, {'T', 't'}, {'U', 'u'},
        {'V', 'v'}, {'W', 'w'}, {'X', 'x'}, {'Y', 'y'}, {'Z', 'z'}
    }};
    
    // List all lowercase letters to check if a character is already lowercase
    constexpr std::array<char, 26> lowercase_letters = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
    };
    
    auto result = std::transform_reduce(
        std::execution::par,
        texts.begin(), texts.end(),
        std::map<char, std::int32_t>(),
        [](const std::map<char, std::int32_t>& a, const std::map<char, std::int32_t>& b) {
            std::map<char, std::int32_t> merged(a);
            for (const auto& entry : b) {
                merged[entry.first] += entry.second;
            }
            return merged;
        },
        [&](const std::string& text) -> std::map<char, std::int32_t> {
            std::map<char, std::int32_t> freq;
            for (char c : text) {
                // Check if it's an uppercase letter
                bool found = false;
                for (const auto& pair : upper_to_lower) {
                    if (c == pair.first) {
                        freq[pair.second] += 1;
                        found = true;
                        break;
                    }
                }
                if (found) {
                    continue;
                }
                // Check if it's a lowercase letter
                for (char lower_char : lowercase_letters) {
                    if (c == lower_char) {
                        freq[c] += 1;
                        break;
                    }
                }
            }
            return freq;
        }
    );
    
    return result;
}

}
