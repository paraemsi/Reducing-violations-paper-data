#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <mutex>
#include <cctype>
#include <map>
#include <vector>
#include <string>
#include <string_view>
#include <functional>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    std::map<char, int> result;
    std::mutex mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string_view& text) {
            // Count frequencies for this text
            std::map<char, int> localCounts;
            for (char c : text) {
                // Check if the character is a letter
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    localCounts[lower_c]++;
                }
            }
            
            // Lock the mutex to update the shared result
            std::lock_guard<std::mutex> lock(mutex);
            for (const auto& pair : localCounts) {
                result[pair.first] += pair.second;
            }
        });
    
    return result;
}

}
