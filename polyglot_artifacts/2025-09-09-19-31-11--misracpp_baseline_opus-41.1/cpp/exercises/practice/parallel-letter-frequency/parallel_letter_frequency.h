#if !defined(PARALLEL_LETTER_FREQUENCY_H)
#define PARALLEL_LETTER_FREQUENCY_H

#include <algorithm>
#include <cctype>
#include <cstddef>
#include <execution>
#include <mutex>
#include <string_view>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {
    template<typename T>
    std::unordered_map<char, std::size_t> frequency(const std::vector<T>& texts) {
        std::unordered_map<char, std::size_t> result;
        std::mutex result_mutex;
        
        // Process each text in parallel
        std::for_each(std::execution::par, texts.begin(), texts.end(),
            [&result, &result_mutex](const T& text) {
                // Local frequency map for this text to reduce lock contention
                std::unordered_map<char, std::size_t> local_freq;
                
                // Count letters in this text
                for (char c : text) {
                    if (std::isalpha(c)) {
                        char lower_c = std::tolower(c);
                        local_freq[lower_c]++;
                    }
                }
                
                // Merge local results into the global result
                std::lock_guard<std::mutex> lock(result_mutex);
                for (const auto& [letter, count] : local_freq) {
                    result[letter] += count;
                }
            });
        
        return result;
    }
}

#endif
