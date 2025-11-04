#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <cstdint>
#include <map>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    if(texts.empty())
    {
        return frequency_map{};
    }

    const std::size_t thread_count {
        std::min<std::size_t>(
            static_cast<std::size_t>(std::thread::hardware_concurrency()),
            texts.size())
    };

    if(thread_count == static_cast<std::size_t>(0U))
    {
        /*  Fallback when hardware_concurrency() returns 0                  */
        return frequency_map{};
    }

    /*  Prepare worker threads                                              */
    std::vector<std::thread> workers {};
    workers.reserve(thread_count);

    std::vector<frequency_map> partial_maps(thread_count);

    const std::size_t chunk_size {
        (texts.size() + thread_count - static_cast<std::size_t>(1U)) / thread_count
    };


    auto worker_fn = [&texts, &partial_maps, chunk_size]
                     (std::size_t index) noexcept
    {
        const std::size_t begin {index * chunk_size};
        const std::size_t end {
            std::min<std::size_t>(begin + chunk_size, texts.size())
        };

        frequency_map& local_map {partial_maps[index]};

        for(std::size_t i {begin}; i < end; ++i)
        {
            const std::string_view line {texts[i]};
            for(const char ch_raw : line)
            {
                const unsigned char uch {static_cast<unsigned char>(ch_raw)};
                if(std::isalpha(static_cast<int>(uch)) != 0)
                {
                    const char lower_ch {
                        static_cast<char>(std::tolower(static_cast<int>(uch)))
                    };

                    ++local_map[lower_ch];
                }
            }
        }
    };

    for(std::size_t idx {0U}; idx < thread_count; ++idx)
    {
        workers.emplace_back(worker_fn, idx);
    }

    for(std::thread& t : workers)
    {
        if(t.joinable())
        {
            t.join();
        }
    }

    /*  Merge partial results                                               */
    frequency_map result {};

    for(const frequency_map& part : partial_maps)
    {
        for(const auto& kv : part)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

} // namespace parallel_letter_frequency
