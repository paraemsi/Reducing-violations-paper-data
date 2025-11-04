#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <mutex>
#include <vector>
#include <string>
#include <array>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Precompute valid letters at compile time
    constexpr std::array<char, 52> valid_letters = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Create a local map for this text
            std::map<char, int> local_counts;
            
            // Count letters in this text
            for (char c : text) {
                // Check if the character is in the valid letters using only equality comparisons
                bool is_letter = false;
                for (char valid_letter : valid_letters) {
                    if ((c == valid_letter)) {
                        is_letter = true;
                        break;
                    }
                }
                if (is_letter) {
                    // Use compound statement
                    local_counts[c]++;
                }
            }
            
            // Merge local_counts into the result
            // Use a lock_guard to protect access to the shared result
            // Add compound statement
            {
                std::lock_guard<std::mutex> lock(result_mutex);
                for (const auto& pair : local_counts) {
                    result[pair.first] += pair.second;
                }
            }
        });
    
    return result;
}

}
