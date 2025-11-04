#include "parallel_letter_frequency.h"
#include <thread>
#include <vector>
#include <map>
#include <cctype>
#include <algorithm>
#include <memory>
#include <cstdint>
#include <functional>
#include <iterator>

namespace parallel_letter_frequency {

std::map<char, std::int32_t> frequency(const std::vector<std::string>& texts) {
    // Handle empty input
    if (texts.empty()) {
        return std::map<char, std::int32_t>();
    }
    
    // Use number of threads equal to the number of texts or available concurrency, whichever is smaller
    const std::size_t num_texts = texts.size();
    std::size_t num_threads = std::thread::hardware_concurrency();
    if (num_threads == 0) {
        num_threads = 1;
    }
    num_threads = std::min(num_threads, num_texts);
    
    std::vector<std::thread> workers;
    std::vector<std::map<char, std::int32_t>> thread_maps(num_threads);
    
    // Split the work into chunks
    const std::size_t chunk_size = (num_texts + num_threads - 1) / num_threads;
    
    for (std::size_t i = 0; i < num_threads; ++i) {
        workers.emplace_back([&, i]() {
            const std::size_t start = i * chunk_size;
            const std::size_t end = std::min(start + chunk_size, num_texts);
            auto& local_map = thread_maps[i];
            
            for (std::size_t j = start; j < end; ++j) {
                for (char c : texts[j]) {
                    // Check if it's a letter
                    if (std::isalpha(static_cast<unsigned char>(c))) {
                        // Convert to lowercase
                        const char lower_c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
                        local_map[lower_c] += 1;
                    }
                }
            }
        });
    }
    
    // Wait for all threads to complete
    for (auto& worker : workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
    
    // Merge all thread maps
    std::map<char, std::int32_t> result;
    for (const auto& map : thread_maps) {
        for (const auto& pair : map) {
            result[pair.first] += pair.second;
        }
    }
    
    return result;
}

}
