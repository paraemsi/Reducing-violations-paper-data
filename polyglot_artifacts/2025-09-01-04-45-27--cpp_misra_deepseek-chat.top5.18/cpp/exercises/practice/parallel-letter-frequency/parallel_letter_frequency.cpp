#include "parallel_letter_frequency.h"
#include <thread>
#include <vector>
#include <map>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <string>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    std::vector<std::thread> threads;
    
    // Function to process a single text
    auto process_text = [&](const std::string& text) {
        std::map<char, int> local_counts;
        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c)) != 0) {
                char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                local_counts[lower_c] += 1;
            }
        }
        
        // Merge with the global result
        std::lock_guard<std::mutex> lock(result_mutex);
        for (const auto& pair : local_counts) {
            result[pair.first] += pair.second;
        }
    };
    
    // Create threads to process each text
    for (const auto& text : texts) {
        threads.emplace_back(process_text, std::cref(text));
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    return result;
}

}
