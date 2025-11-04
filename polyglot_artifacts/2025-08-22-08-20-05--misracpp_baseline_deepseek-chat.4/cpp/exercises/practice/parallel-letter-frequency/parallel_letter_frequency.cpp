#include "parallel_letter_frequency.h"
#include <thread>
#include <vector>
#include <map>
#include <cctype>
#include <string>
#include <algorithm>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) {
        return std::map<char, int>();
    }
    
    // Determine the number of threads to use
    unsigned int num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }
    // Ensure we don't create more threads than there are texts
    num_threads = std::min(num_threads, static_cast<unsigned int>(texts.size()));
    
    // Split the texts among threads
    std::vector<std::thread> threads;
    std::vector<std::map<char, int>> thread_results(num_threads);
    
    // Function to process a range of texts
    auto process_range = [&texts](std::map<char, int>& result, size_t start, size_t end) {
        for (size_t i = start; i < end; ++i) {
            const std::string& text = texts[i];
            for (char c : text) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    // Convert to lowercase
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    result[lower_c]++;
                }
            }
        }
    };
    
    // Launch threads
    size_t chunk_size = texts.size() / num_threads;
    size_t start = 0;
    for (unsigned int i = 0; i < num_threads; ++i) {
        size_t end = (i == num_threads - 1) ? texts.size() : start + chunk_size;
        threads.emplace_back(process_range, 
                             std::ref(thread_results[i]), 
                             start, end);
        start = end;
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Combine results from all threads
    std::map<char, int> final_result;
    for (const auto& result : thread_results) {
        for (const auto& pair : result) {
            final_result[pair.first] += pair.second;
        }
    }
    
    return final_result;
}

}
