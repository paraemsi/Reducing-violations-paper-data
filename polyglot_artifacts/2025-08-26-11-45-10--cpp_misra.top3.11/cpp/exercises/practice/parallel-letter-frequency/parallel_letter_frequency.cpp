#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>
#include <map>
#include <cstdint>

namespace parallel_letter_frequency {

namespace {
    // Helper: process a range of texts and count letter frequencies
    void count_letters(const std::vector<std::string>& texts, std::size_t start, std::size_t end, letter_frequency_map& freq_map, std::mutex& map_mutex)
    {
        letter_frequency_map local_map;
        for(std::size_t i = start; i < end; ++i)
        {
            for(const char ch : texts[i])
            {
                if((std::isalpha(static_cast<unsigned char>(ch))) != 0)
                {
                    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                    ++(local_map[lower]);
                }
            }
        }
        // Merge local_map into shared freq_map
        std::lock_guard<std::mutex> lock(map_mutex);
        for(const auto& kv : local_map)
        {
            freq_map[kv.first] += kv.second;
        }
    }
}

letter_frequency_map frequency(const std::vector<std::string>& texts)
{
    letter_frequency_map freq_map;
    std::mutex map_mutex;

    const std::size_t num_texts = texts.size();
    if(num_texts == 0U)
    {
        return freq_map;
    }

    const std::size_t num_threads = (std::min)(std::thread::hardware_concurrency(), static_cast<unsigned int>(num_texts));
    std::vector<std::thread> threads;
    std::vector<std::size_t> starts;
    std::vector<std::size_t> ends;

    // Calculate chunk sizes
    std::size_t chunk_size = num_texts / ((num_threads == 0U) ? 1U : num_threads);
    std::size_t remainder = num_texts % ((num_threads == 0U) ? 1U : num_threads);

    std::size_t current = 0U;
    for(std::size_t i = 0U; i < num_threads; ++i)
    {
        std::size_t this_chunk = chunk_size + ((i < remainder) ? 1U : 0U);
        starts.push_back(current);
        ends.push_back(current + this_chunk);
        current += this_chunk;
    }

    for(std::size_t i = 0U; i < num_threads; ++i)
    {
        threads.emplace_back(count_letters, std::cref(texts), starts[i], ends[i], std::ref(freq_map), std::ref(map_mutex));
    }

    for(auto& t : threads)
    {
        t.join();
    }

    return freq_map;
}

}
