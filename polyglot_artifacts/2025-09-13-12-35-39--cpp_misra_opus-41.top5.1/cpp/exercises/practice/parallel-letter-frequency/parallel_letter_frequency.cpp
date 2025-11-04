#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <cctype>
#include <mutex>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    frequency_map result;
    std::mutex result_mutex;
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&result, &result_mutex](const std::string_view& text) {
            // Create a local frequency map for this text
            frequency_map local_freq;
            
            // Count letters in the current text
            for (char c : text) {
                // Check if character is alphabetic using unsigned char cast
                unsigned char uc = static_cast<unsigned char>(c);
                if (std::isalpha(uc)) {
                    // Convert to lowercase for case-insensitive counting
                    unsigned char lower_uc = static_cast<unsigned char>(std::tolower(uc));
                    char lower_c = static_cast<char>(lower_uc);
                    local_freq[lower_c]++;
                }
            }
            
            // Merge local results into the global result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_freq) {
                result[pair.first] = result[pair.first] + pair.second;
            }
        });
    
    return result;
}

}
