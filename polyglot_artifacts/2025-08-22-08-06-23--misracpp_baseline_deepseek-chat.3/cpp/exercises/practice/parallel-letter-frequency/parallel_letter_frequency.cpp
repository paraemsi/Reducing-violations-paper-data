#include "parallel_letter_frequency.h"
#include <thread>
#include <vector>
#include <mutex>
#include <map>
#include <string>
#include <cctype>
#include <functional>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    std::vector<std::thread> threads;
    
    // Reserve space to avoid reallocations
    threads.reserve(texts.size());
    
    for (const auto& text : texts) {
        threads.emplace_back([&result, &result_mutex, &text]() {
            // Count frequencies in this text
            std::map<char, int> local_counts;
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    local_counts[lower_c]++;
                }
            }
            
            // Merge with the global result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_counts) {
                result[pair.first] += pair.second;
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    return result;
}

}
