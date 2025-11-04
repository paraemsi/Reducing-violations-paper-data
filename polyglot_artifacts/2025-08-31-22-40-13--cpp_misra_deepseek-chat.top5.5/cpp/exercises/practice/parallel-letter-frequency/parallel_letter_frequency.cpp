#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <mutex>
#include <cctype>
#include <map>
#include <vector>
#include <string>
#include <functional>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Count frequencies for this text
            std::map<char, int> local_counts;
            for (char c : text) {
                // Check if it's a letter using unsigned char to avoid issues
                unsigned char uc = static_cast<unsigned char>(c);
                if (std::isalpha(uc) != 0) {
                    // Convert to lowercase
                    char lower_c = static_cast<char>(std::tolower(uc));
                    ++local_counts[lower_c];
                }
            }
            
            // Merge into the global result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                result[pair.first] += pair.second;
            }
        });
    
    return result;
}

}
