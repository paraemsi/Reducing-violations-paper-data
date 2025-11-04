#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <cctype>
#include <map>
#include <vector>
#include <string>
#include <cstdint>
#include <atomic>
#include <array>
#include <string_view>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string_view>& texts) {
    // Create an array of atomic integers for each letter 'a' to 'z'
    std::array<std::atomic<std::int32_t>, 26> counts;
    // Initialize all counts to 0
    for (auto& count : counts) {
        count.store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&counts](const std::string_view& text) {
            for (char c : text) {
                // Check if it's a letter using unsigned char to avoid UB
                const unsigned char uc = static_cast<unsigned char>(c);
                if (std::isalpha(uc) != 0) {
                    // Convert to lowercase
                    const char lower_c = static_cast<char>(std::tolower(uc));
                    // Calculate index - 'a' to 'z' are consecutive in ASCII
                    // Ensure the index is within bounds
                    const std::int32_t index = static_cast<std::int32_t>(lower_c) - static_cast<std::int32_t>('a');
                    if ((index >= 0) && (index < 26)) {
                        // Atomically increment the count
                        counts[index].fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }
        });
    
    // Convert the array to a map
    std::map<char, std::int32_t> result;
    for (std::int32_t i = 0; i < 26; ++i) {
        const char current_char = static_cast<char>(static_cast<std::int32_t>('a') + i);
        result[current_char] = counts[i].load(std::memory_order_relaxed);
    }
    return result;
}

}
