#include "parallel_letter_frequency.h"
#include <map>
#include <mutex>
#include <cctype>
#include <array>
#include <vector>
#include <thread>
#include <functional>
#include <memory>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::array<int, 26> global_counts{};
    std::mutex mtx;
    
    // Function to process a single text
    auto process_text = [&](const std::string& text) {
        std::array<int, 26> local_counts{};
        for (char c : text) {
            if (std::isalpha(static_cast<unsigned char>(c))) {
                char lower_c = std::tolower(static_cast<unsigned char>(c));
                local_counts[lower_c - 'a']++;
            }
        }
        
        // Lock to update global counts
        std::lock_guard<std::mutex> lock(mtx);
        for (int i = 0; i < 26; i++) {
            global_counts[i] += local_counts[i];
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
    
    // Convert to map
    std::map<char, int> result;
    for (int i = 0; i < 26; i++) {
        if (global_counts[i] > 0) {
            result[static_cast<char>('a' + i)] = global_counts[i];
        }
    }
    return result;
}

}
