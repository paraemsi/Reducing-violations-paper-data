#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <cctype>
#include <map>
#include <cstdint>
#include <atomic>
#include <vector>
#include <array>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Use a fixed-size array for the 26 letters
    std::array<std::atomic<std::int32_t>, 26> frequencies;
    // Initialize all atomics to zero
    for (auto& freq : frequencies) {
        freq.store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            for (char c : text) {
                // Check if it's a letter using isalpha
                // Cast to unsigned char to avoid UB
                unsigned char uc = static_cast<unsigned char>(c);
                if (std::isalpha(uc) != 0) {
                    // Convert to lowercase
                    char lower_c = static_cast<char>(std::tolower(uc));
                    // Calculate index ensuring it's within bounds
                    std::int32_t index = (static_cast<std::int32_t>(lower_c) - static_cast<std::int32_t>('a'));
                    // Ensure index is valid
                    if ((index >= 0) && (index < 26)) {
                        // Atomically increment the count
                        frequencies[index].fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }
        });
    
    // Convert to the required result format
    std::map<char, int> result;
    for (std::int32_t i = 0; i < 26; ++i) {
        char current_char = static_cast<char>(static_cast<std::int32_t>('a') + i);
        result[current_char] = static_cast<int>(frequencies[i].load());
    }
    return result;
}

}
