#include "parallel_letter_frequency.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>
#include <algorithm>
#include <execution>
#include <mutex>
#include <string_view>

namespace parallel_letter_frequency {

std::unordered_map<char, int> frequency(const std::vector<std::string_view>& texts) {
    std::unordered_map<char, int> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&result, &result_mutex](const std::string_view& text) {
            // Count frequencies in this text
            std::unordered_map<char, int> local_counts;
            for (char c : text) {
                // Check if the character is a letter
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    local_counts[c]++;
                }
            }
            
            // Merge with the global result while holding the lock
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                result[pair.first] += pair.second;
            }
        });
    
    return result;
}

}
