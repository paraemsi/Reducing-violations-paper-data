#include "parallel_letter_frequency.h"
#include <execution>
#include <algorithm>
#include <map>
#include <mutex>
#include <vector>
#include <string_view>
#include <unordered_set>

namespace parallel_letter_frequency {

std::map<char, counter_t> frequency(const std::vector<std::string_view>& texts) {
    // To store the result
    std::map<char, counter_t> result;
    // Mutex to protect access to the result map
    std::mutex result_mutex;
    
    // Create a set of all valid letters using character literals
    // Since we can't use relational operators with characters, we'll list all letters explicitly
    std::unordered_set<char> letters = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string_view& text) {
            // Create a local map to count frequencies for this text
            std::map<char, counter_t> local_counts;
            for (char c : text) {
                // Check if the character is in the set of letters using find
                // find uses == internally which is allowed
                // Add parentheses to ensure proper precedence
                if ((letters.find(c) != letters.end())) {
                    local_counts[c]++;
                }
            }
            
            // Merge local_counts into the result map
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                result[pair.first] += pair.second;
            }
        });
    
    return result;
}

}
