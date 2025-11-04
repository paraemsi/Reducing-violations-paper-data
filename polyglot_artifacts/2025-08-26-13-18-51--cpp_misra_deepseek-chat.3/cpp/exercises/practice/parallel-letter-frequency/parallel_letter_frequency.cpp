#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <map>
#include <vector>
#include <cctype>
#include <cstdint>
#include <atomic>
#include <array>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Use an array for all possible unsigned char values to avoid map access issues
    constexpr size_t num_chars = 1 << (8 * sizeof(unsigned char));
    std::array<std::atomic<std::int32_t>, num_chars> counts;
    
    // Initialize all counts to 0
    for (auto& count : counts) {
        count.store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            for (char c : text) {
                // Convert to unsigned char to use as index
                unsigned char uc = static_cast<unsigned char>(c);
                if (std::isalpha(uc)) {
                    // Convert to lowercase and use as index
                    unsigned char lower_uc = static_cast<unsigned char>(std::tolower(uc));
                    counts[lower_uc].fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    
    // Convert to the required result type, only including letters that have non-zero counts
    std::map<char, int> result;
    for (size_t i = 0; i < num_chars; ++i) {
        int count_val = static_cast<int>(counts[i].load(std::memory_order_relaxed));
        if (count_val > 0) {
            // Check if the index corresponds to a letter
            unsigned char uc = static_cast<unsigned char>(i);
            if (std::isalpha(uc)) {
                result[static_cast<char>(uc)] = count_val;
            }
        }
    }
    
    return result;
}

}
