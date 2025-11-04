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
        return {};
    }

    // Determine number of threads to use
    const unsigned int num_threads = std::max(1u, static_cast<unsigned int>(std::thread::hardware_concurrency()));
    std::vector<std::thread> threads;
    std::vector<std::map<char, int>> partial_results(num_threads);
    
    // Calculate chunk size for each thread
    const size_t total_texts = texts.size();
    const size_t chunk_size = (total_texts + num_threads - 1) / num_threads;
    
    for (unsigned int i = 0; i < num_threads; ++i) {
        const size_t start_index = i * chunk_size;
        if (start_index >= total_texts) {
            break;
        }
        const size_t end_index = std::min(start_index + chunk_size, total_texts);
        
        threads.emplace_back(
            [&texts, &partial_results, i, start_index, end_index]() {
                auto& local_map = partial_results[i];
                for (size_t j = start_index; j < end_index; ++j) {
                    for (unsigned char c : texts[j]) {
                        if (std::isalpha(c)) {
                            // Convert to lowercase and count
                            char lower_c = static_cast<char>(std::tolower(c));
                            local_map[lower_c] += 1;
                        }
                    }
                }
            }
        );
    }
    
    // Join all threads
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
    
    // Merge partial results
    std::map<char, int> result;
    for (const auto& partial : partial_results) {
        for (const auto& pair : partial) {
            result[pair.first] += pair.second;
        }
    }
    
    return result;
}

}
