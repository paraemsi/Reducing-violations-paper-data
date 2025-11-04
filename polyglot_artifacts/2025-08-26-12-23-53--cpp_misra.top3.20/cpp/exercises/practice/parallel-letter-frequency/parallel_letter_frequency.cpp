#include "parallel_letter_frequency.h"
#include <thread>
#include <mutex>
#include <algorithm>
#include <cctype>
#include <vector>
#include <iterator>

namespace parallel_letter_frequency {

letter_frequency_map frequency(const std::vector<std::string>& texts) noexcept {
    return letter_frequency(texts);
}

namespace {
    // Helper: count letters in a range of strings
    void count_letters(const std::vector<std::string>& texts, std::size_t start, std::size_t end, letter_frequency_map& freq, std::mutex& freq_mutex)
    {
        letter_frequency_map local_freq;
        for(std::size_t i = start; i < end; ++i)
        {
            for(char ch : texts[i])
            {
                if(std::isalpha(static_cast<unsigned char>(ch)))
                {
                    char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                    ++local_freq[lower];
                }
            }
        }
        // Merge local_freq into shared freq
        std::lock_guard<std::mutex> lock(freq_mutex);
        for(const auto& kv : local_freq)
        {
            freq[kv.first] += kv.second;
        }
    }
}

letter_frequency_map letter_frequency(const std::vector<std::string>& texts) noexcept
{
    letter_frequency_map freq;
    std::mutex freq_mutex;

    std::size_t num_texts = texts.size();
    if(num_texts == 0U)
    {
        return freq;
    }

    unsigned int num_threads = std::thread::hardware_concurrency();
    if(num_threads == 0U)
    {
        num_threads = 2U;
    }
    if(num_threads > num_texts)
    {
        num_threads = static_cast<unsigned int>(num_texts);
    }

    std::vector<std::thread> threads;
    std::vector<std::size_t> starts;
    std::vector<std::size_t> ends;

    std::size_t block_size = num_texts / num_threads;
    std::size_t remainder = num_texts % num_threads;

    std::size_t current = 0U;
    for(unsigned int t = 0U; t < num_threads; ++t)
    {
        std::size_t this_block = block_size + ((t < remainder) ? 1U : 0U);
        starts.push_back(current);
        ends.push_back(current + this_block);
        current += this_block;
    }

    for(unsigned int t = 0U; t < num_threads; ++t)
    {
        threads.emplace_back(count_letters, std::cref(texts), starts[t], ends[t], std::ref(freq), std::ref(freq_mutex));
    }

    for(auto& th : threads)
    {
        th.join();
    }

    return freq;
}

}
