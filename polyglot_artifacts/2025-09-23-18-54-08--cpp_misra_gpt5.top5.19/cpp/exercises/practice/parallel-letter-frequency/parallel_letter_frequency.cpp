#include "parallel_letter_frequency.h"

#include <cctype>
#include <cstdint>
#include <cstddef>
#include <mutex>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    frequency_map global{};
    std::mutex mtx{};

    const std::size_t n = texts.size();
    // Use up to 4 threads, but not more than the number of texts; at least 1 thread.
    const std::size_t max_threads = static_cast<std::size_t>(4ULL);
    std::size_t threads_count = (n < max_threads) ? ((n == static_cast<std::size_t>(0ULL)) ? static_cast<std::size_t>(1ULL) : n) : max_threads;

    const std::size_t block_size = (n == static_cast<std::size_t>(0ULL))
        ? static_cast<std::size_t>(0ULL)
        : ((n + (threads_count - static_cast<std::size_t>(1ULL))) / threads_count);

    std::vector<std::thread> threads{};
    threads.reserve(threads_count);

    for (std::size_t t = static_cast<std::size_t>(0ULL); (t < threads_count); ++t)
    {
        const std::size_t begin = (t * block_size);
        std::size_t end = (begin + block_size);
        if ((end > n))
        {
            end = n;
        }

        threads.emplace_back([begin, end, &texts, &global, &mtx]() {
            frequency_map local{};

            for (std::size_t i = begin; (i < end); ++i)
            {
                const std::string_view& s = texts[i];
                const std::size_t len = s.size();

                for (std::size_t j = static_cast<std::size_t>(0ULL); (j < len); ++j)
                {
                    const unsigned char uch = static_cast<unsigned char>(s[j]);
                    if ((std::isalpha(static_cast<int>(uch))) != 0)
                    {
                        const char lower_c =
                            static_cast<char>(std::tolower(static_cast<int>(uch)));
                        ++local[lower_c];
                    }
                }
            }

            {
                std::lock_guard<std::mutex> lock(mtx);
                for (const auto& kv : local)
                {
                    global[kv.first] += kv.second;
                }
            }
        });
    }

    for (std::size_t t = static_cast<std::size_t>(0ULL); (t < threads.size()); ++t)
    {
        threads[t].join();
    }

    return global;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::string_view> views{};
    views.reserve(texts.size());
    for (std::size_t i = static_cast<std::size_t>(0ULL); (i < texts.size()); ++i)
    {
        views.emplace_back(texts[i]);
    }
    return frequency(views);
}

}
