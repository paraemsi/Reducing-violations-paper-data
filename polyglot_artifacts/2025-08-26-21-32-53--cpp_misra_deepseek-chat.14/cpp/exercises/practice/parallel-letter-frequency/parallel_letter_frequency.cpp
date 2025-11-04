#include "parallel_letter_frequency.h"
#include <execution>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <cctype>
#include <thread>
#include <mutex>
#include <array>
#include <memory>
#include <atomic>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    // Number of letters in the alphabet
    constexpr std::int32_t num_letters = 26;
    
    // Use atomics for each letter count
    std::array<std::atomic<std::int32_t>, num_letters> global_counts;
    for (std::int32_t i = 0; i < num_letters; ++i) {
        global_counts[i].store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            // Process each character in the text
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    // 'a' to 'z' are consecutive in ASCII
                    std::int32_t index = static_cast<std::int32_t>(lower_c - 'a');
                    global_counts[index].fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    
    // Convert to the required map format
    std::map<char, int> result;
    for (std::int32_t i = 0; i < num_letters; ++i) {
        char c = static_cast<char>('a' + i);
        result[c] = global_counts[i].load(std::memory_order_relaxed);
    }
    
    return result;
}

}
