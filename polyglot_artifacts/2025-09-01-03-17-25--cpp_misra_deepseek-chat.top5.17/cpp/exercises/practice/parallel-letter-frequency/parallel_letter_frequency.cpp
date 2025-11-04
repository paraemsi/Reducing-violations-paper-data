#include "parallel_letter_frequency.h"
#include <map>
#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <cctype>
#include <functional>
#include <algorithm>
#include <memory>
#include <iterator>
#include <cstdint>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) {
        return {};
    }
    
    // Determine number of threads to use
    const unsigned int num_threads = std::thread::hardware_concurrency();
    const std::size_t num_texts = texts.size();
    
    // We can't have more threads than texts
    const unsigned int actual_num_threads = std::min(
        static_cast<unsigned int>(num_texts), 
        (num_threads != 0) ? num_threads : 2
    );
    
    std::vector<std::thread> threads;
    std::vector<std::map<char, int>> thread_results(actual_num_threads);
    
    // Lambda for each thread to process its chunk of texts
    auto process_chunk = [&texts](std::size_t start, std::size_t end, std::map<char, int>& result) {
        for (std::size_t i = start; i < end; ++i) {
            for (char c : texts[i]) {
                if (std::isalpha(static_cast<unsigned char>(c))) {
                    char lower_c = std::tolower(static_cast<unsigned char>(c));
                    result[lower_c]++;
                }
            }
        }
    };
    
    // Start threads
    std::size_t chunk_size = num_texts / actual_num_threads;
    for (unsigned int i = 0; i < actual_num_threads; ++i) {
        std::size_t start = i * chunk_size;
        std::size_t end = (i == actual_num_threads - 1) ? num_texts : start + chunk_size;
        threads.emplace_back(process_chunk, start, end, std::ref(thread_results[i]));
    }
    
    // Wait for all threads to complete
    for (auto& thread : threads) {
        thread.join();
    }
    
    // Merge results from all threads
    std::map<char, int> final_result;
    for (const auto& partial_result : thread_results) {
        for (const auto& entry : partial_result) {
            final_result[entry.first] += entry.second;
        }
    }
    
    return final_result;
}

}
