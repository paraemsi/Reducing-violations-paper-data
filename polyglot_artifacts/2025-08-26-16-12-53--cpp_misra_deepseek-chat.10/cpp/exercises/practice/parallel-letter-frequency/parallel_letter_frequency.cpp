#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <atomic>
#include <array>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Use fixed-width integer type for the counters
    std::array<std::atomic<std::int32_t>, 26> freqs;
    // Initialize all atomics to 0
    for (std::int32_t i = 0; i < 26; ++i) {
        freqs[i].store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            for (char c : text) {
                // Check if it's a letter using unsigned char to avoid UB
                if (std::isalpha(static_cast<unsigned char>(c)) != 0) {
                    // Convert to lowercase
                    char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                    // Calculate index (0-25)
                    // Ensure the operation is within bounds
                    std::int32_t index = static_cast<std::int32_t>(static_cast<std::int32_t>(lower_c) - static_cast<std::int32_t>('a'));
                    // Atomically increment the count
                    if ((index >= 0) && (index < 26)) {
                        freqs[index].fetch_add(1, std::memory_order_relaxed);
                    }
                }
            }
        });
    
    // Convert to the required map format, casting to int
    std::map<char, int> result;
    for (std::int32_t i = 0; i < 26; ++i) {
        char c = static_cast<char>(static_cast<std::int32_t>('a') + i);
        // Cast the loaded value to int to match the function signature
        result[c] = static_cast<int>(freqs[i].load(std::memory_order_relaxed));
    }
    return result;
}

}
