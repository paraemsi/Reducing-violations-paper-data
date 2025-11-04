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
    // Helper: merge two frequency maps
    void merge_maps(letter_frequency_map& target, const letter_frequency_map& source)
    {
        for(const auto& kv : source)
        {
            target[kv.first] += kv.second;
        }
    }

    // Helper: count letters in a string
    letter_frequency_map count_letters(const std::string& text)
    {
        letter_frequency_map freq;
        for(const char ch : text)
        {
            if((std::isalpha(static_cast<unsigned char>(ch))) != 0)
            {
                char lower = static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                ++freq[lower];
            }
        }
        return freq;
    }
}

letter_frequency_map letter_frequency(const std::vector<std::string>& texts)
{
    std::vector<std::thread> threads;
    std::vector<letter_frequency_map> partial_results;
    std::mutex results_mutex;

    const std::size_t num_texts = texts.size();
    partial_results.resize(num_texts);

    for(std::size_t i = 0U; i < num_texts; ++i)
    {
        threads.emplace_back(
            [&texts, &partial_results, i]()
            {
                partial_results[i] = count_letters(texts[i]);
            }
        );
    }

    for(std::thread& t : threads)
    {
        if(t.joinable())
        {
            t.join();
        }
    }

    letter_frequency_map result;
    for(const auto& freq : partial_results)
    {
        merge_maps(result, freq);
    }

    return result;
}

// Alias for backward compatibility with test suite
letter_frequency_map frequency(const std::vector<std::string>& texts)
{
    return letter_frequency(texts);
}

}
