#include "parallel_letter_frequency.h"

#include <algorithm>
#include <future>
#include <locale>
#include <thread>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    if(texts.empty())
    {
        return frequency_map{};
    }

    const std::size_t hardware_threads =
        (std::thread::hardware_concurrency() == 0U)
            ? 2U
            : static_cast<std::size_t>(std::thread::hardware_concurrency());

    const std::size_t thread_count =
        (texts.size() < hardware_threads) ? texts.size() : hardware_threads;

    const std::size_t chunk_size =
        (texts.size() + (thread_count - 1U)) / thread_count;

    std::vector< std::future<frequency_map> > futures{};
    futures.reserve(thread_count);

    

    for(std::size_t i{0U}; i < thread_count; ++i)
    {
        const std::size_t begin{ i * chunk_size };
        const std::size_t end{ std::min((i + 1U) * chunk_size, texts.size()) };

        futures.emplace_back(
            std::async(
                std::launch::async,
                [begin, end, &texts]() -> frequency_map
                {
                    const std::string letters{"abcdefghijklmnopqrstuvwxyz"};
                    const std::locale loc{};
                    frequency_map local_counts{};

                    for(std::size_t idx{begin}; idx < end; ++idx)
                    {
                        for(const char ch_raw : texts[idx])
                        {
                            const char ch_lower{
                                std::tolower(
                                    ch_raw,
                                    loc)};

                            if(letters.find(ch_lower) != std::string::npos)
                            {
                                ++local_counts[ch_lower];
                            }
                        }
                    }

                    return local_counts;
                }));
    }

    frequency_map total_counts{};

    for(std::future<frequency_map>& fut : futures)
    {
        const frequency_map part{fut.get()};
        for(const auto& kv : part)
        {
            total_counts[kv.first] += kv.second;
        }
    }

    return total_counts;
}

frequency_map frequency(const std::vector<std::string>& texts)
{
    std::vector<std::string_view> views{};
    views.reserve(texts.size());
    for(const std::string& s : texts)
    {
        views.emplace_back(s);
    }
    return frequency(views);
}

} // namespace parallel_letter_frequency
