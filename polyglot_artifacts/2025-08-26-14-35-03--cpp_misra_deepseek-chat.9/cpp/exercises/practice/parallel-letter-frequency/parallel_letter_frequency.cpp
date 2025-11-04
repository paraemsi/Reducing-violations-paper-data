#include "parallel_letter_frequency.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

namespace parallel_letter_frequency {

std::map<char, Counter> frequency(const std::vector<std::string>& texts) {
    std::map<char, Counter> result;
    std::mutex result_mutex;
    
    // Function to process each text
    auto process_text = [&result, &result_mutex](const std::string& text) {
        std::map<char, Counter> local_freq;
        for (char c : text) {
            if ((std::isalpha(static_cast<unsigned char>(c)) != 0)) {
                // Convert to lowercase
                char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                local_freq[lower_c] += static_cast<Counter>(1);
            }
        }
        
        // Merge with the global result
        std::lock_guard<std::mutex> lock(result_mutex);
        for (const auto& pair : local_freq) {
            result[pair.first] += pair.second;
        }
    };
    
    // Handle case when there are no texts
    if (texts.empty()) {
        return result;
    }
    
    // Determine the number of threads to use
    // Use at least 1 thread if hardware_concurrency returns 0
    const size_t num_threads = (std::thread::hardware_concurrency() > static_cast<unsigned int>(0)) ? 
                               std::thread::hardware_concurrency() : static_cast<size_t>(1);
    std::vector<std::thread> threads;
    threads.reserve(num_threads);
    
    // Distribute the work among threads
    for (size_t i = 0; i < num_threads; ++i) {
        threads.emplace_back([&, i]() {
            // Process texts in chunks
            for (size_t j = i; j < texts.size(); j += num_threads) {
                process_text(texts[j]);
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
