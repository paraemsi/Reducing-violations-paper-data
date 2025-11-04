#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <vector>
#include <map>
#include <cctype>
#include <atomic>
#include <array>
#include <string_view>
#include <memory>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    // Use a fixed-size array of atomics
    // Since std::atomic is not copyable, we need to initialize them in a way that's valid
    // Let's use a unique_ptr to manage the memory
    auto counts_ptr = std::make_unique<std::atomic<int>[]>(26);
    std::atomic<int>* counts = counts_ptr.get();
    
    // Initialize all elements to 0
    for (int i = 0; i < 26; ++i) {
        counts[i].store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [counts](const std::string_view& text) {
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    // Increment the corresponding atomic counter
                    int index = lower_c - 'a';
                    counts[index].fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    
    // Build the result map
    std::map<char, int> result;
    for (int i = 0; i < 26; ++i) {
        char c = 'a' + i;
        int count = counts[i].load(std::memory_order_relaxed);
        if (count > 0) {
            result[c] = count;
        }
    }
    return result;
}

}
