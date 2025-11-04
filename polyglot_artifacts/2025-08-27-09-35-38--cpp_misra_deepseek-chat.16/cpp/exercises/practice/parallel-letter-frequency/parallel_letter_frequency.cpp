#include "parallel_letter_frequency.h"
#include <algorithm>
#include <execution>
#include <cctype>
#include <map>
#include <vector>
#include <string>
#include <atomic>
#include <array>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, counter_t> frequency(const std::vector<std::string>& texts) {
    // Create an array of atomic integers for each letter
    std::array<std::atomic<counter_t>, 26> counts;
    for (auto& count : counts) {
        count.store(0, std::memory_order_relaxed);
    }
    
    // Process each text in parallel
    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&](const std::string& text) {
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    counter_t index = static_cast<counter_t>((lower_c - 'a'));
                    counts[index].fetch_add(1, std::memory_order_relaxed);
                }
            }
        });
    
    // Convert the array to a map
    std::map<char, counter_t> result;
    for (counter_t i = 0; i < 26; i++) {
        char c = static_cast<char>(('a' + i));
        counter_t count = counts[i].load(std::memory_order_relaxed);
        if ((count > 0)) {
            result[c] = count;
        }
    }
    
    return result;
}

}
