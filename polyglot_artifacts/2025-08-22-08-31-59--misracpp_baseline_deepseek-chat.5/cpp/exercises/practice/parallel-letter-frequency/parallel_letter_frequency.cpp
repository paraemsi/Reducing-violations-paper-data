#include "parallel_letter_frequency.h"
#include <algorithm>
#include <map>
#include <cctype>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <functional>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Lambda function to process each text
    auto process_text = [&result, &result_mutex](const std::string& text) {
        std::map<char, int> local_freq;
        for (unsigned char c : text) {
            if (std::isalpha(c)) {
                char lower_c = std::tolower(c);
                local_freq[lower_c]++;
            }
        }
        
        // Merge local frequencies into the result
        std::lock_guard<std::mutex> lock(result_mutex);
        for (const auto& entry : local_freq) {
            result[entry.first] += entry.second;
        }
    };
    
    // Create threads to process each text
    std::vector<std::thread> threads;
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
