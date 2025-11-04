#include "parallel_letter_frequency.h"
#include <map>
#include <vector>
#include <string>
#include <cctype>
#include <mutex>
#include <thread>
#include <functional>
#include <vector>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::map<char, int> result;
    std::mutex result_mutex;
    
    // Number of threads to use
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) num_threads = 1;
    
    // Split the work among threads
    std::vector<std::thread> threads;
    size_t chunk_size = texts.size() / num_threads;
    
    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? texts.size() : start + chunk_size;
        
        threads.emplace_back([&result, &result_mutex, &texts, start, end]() {
            // Local frequency map for this thread's chunk
            std::map<char, int> local_freq;
            
            // Process each text in the assigned chunk
            for (size_t j = start; j < end; ++j) {
                const std::string& text = texts[j];
                for (char c : text) {
                    if (std::isalpha(static_cast<unsigned char>(c))) {
                        char lower_c = std::tolower(static_cast<unsigned char>(c));
                        ++local_freq[lower_c];
                    }
                }
            }
            
            // Merge local frequencies into the result
            std::lock_guard<std::mutex> lock(result_mutex);
            for (const auto& pair : local_freq) {
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
