#include "parallel_letter_frequency.h"
#include <vector>
#include <string>
#include <string_view>
#include <map>
#include <thread>
#include <mutex>
#include <cctype>
#include <functional>
#include <memory>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    std::vector<std::thread> threads;
    
    for (const auto& text : texts) {
        threads.emplace_back([&result, &result_mutex, text]() {
            std::map<char, int> local_counts;
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    local_counts[lower_c]++;
                }
            }
            
            // Lock the result map and update it
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& entry : local_counts) {
                result[entry.first] += entry.second;
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
