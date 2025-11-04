#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <mutex>
#include <cctype>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string>& texts) {
    std::map<char, std::int32_t> result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Local map to count frequencies for this text
            std::map<char, std::int32_t> local_counts;
            
            // Count letters in the current text
            for (char c : text) {
                // Cast to unsigned char for ctype functions
                unsigned char uc = static_cast<unsigned char>(c);
                if ((std::isalpha(uc)) != 0) {
                    char lower_c = static_cast<char>(std::tolower(uc));
                    // Ensure proper parenthesization
                    local_counts[lower_c] = (local_counts[lower_c] + static_cast<std::int32_t>(1));
                }
            }
            
            // Merge local counts into the result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                result[pair.first] = (result[pair.first] + pair.second);
            }
        });
    
    return result;
}

}
