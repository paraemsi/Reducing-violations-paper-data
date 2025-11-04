#include "parallel_letter_frequency.h"
#include <map>
#include <mutex>
#include <cctype>
#include <thread>
#include <vector>
#include <functional>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Number of threads to use
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }
    
    // Split the work among threads
    std::vector<std::thread> threads;
    size_t chunk_size = (texts.size() + num_threads - 1) / num_threads;
    
    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = std::min(start + chunk_size, texts.size());
        if (start >= texts.size()) {
            break;
        }
        
        threads.emplace_back([&result, &result_mutex, &texts, start, end]() {
            // Process each text in the assigned range
            for (size_t j = start; j < end; ++j) {
                const std::string& text = texts[j];
                std::map<char, int> local_map;
                for (char c : text) {
                    // Check if it's a letter
                    if ((std::isalpha(static_cast<unsigned char>(c)) != 0)) {
                        // Convert to lowercase
                        char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                        local_map[lower_c]++;
                    }
                }
                // Lock and merge into the result
                std::lock_guard<std::mutex> lock(result_mutex);
                for (const auto& pair : local_map) {
                    result[pair.first] += pair.second;
                }
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
