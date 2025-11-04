#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <string_view>
#include <thread>

namespace parallel_letter_frequency {

static auto count_letters_in_text(const std::string& text) -> frequency_map
{
    frequency_map local_counts {};

    for (const char ch_raw : text)
    {
        const unsigned char ch_uc { static_cast<unsigned char>(ch_raw) };
        if (std::isalpha(static_cast<int>(ch_uc)) != 0)
        {
            const char letter { static_cast<char>(std::tolower(static_cast<int>(ch_uc))) };
            ++local_counts[letter];
        }
    }

    return local_counts;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    if (texts.empty())
    {
        return {};
    }

    const std::size_t hw_threads { static_cast<std::size_t>(std::thread::hardware_concurrency()) };
    const std::size_t thread_count { (hw_threads > 0U) ? std::min(texts.size(), hw_threads) : texts.size() };

    const std::size_t chunk_size { (texts.size() + thread_count - 1U) / thread_count };

    std::vector<std::thread> workers {};
    std::vector<frequency_map> partial_results(thread_count);

    for (std::size_t t { 0U }; t < thread_count; ++t)
    {
        const std::size_t begin { t * chunk_size };
        const std::size_t end   { std::min((t + 1U) * chunk_size, texts.size()) };

        workers.emplace_back(
            [&texts, &partial_results, t, begin, end]()
            {
                for (std::size_t idx { begin }; idx < end; ++idx)
                {
                    const frequency_map local { count_letters_in_text(texts[idx]) };
                    for (const auto& [letter, cnt] : local)
                    {
                        partial_results[t][letter] += cnt;
                    }
                }
            });
    }

    for (std::thread& w : workers)
    {
        w.join();
    }

    frequency_map total {};

    for (const frequency_map& part : partial_results)
    {
        for (const auto& [letter, cnt] : part)
        {
            total[letter] += cnt;
        }
    }

    return total;
}

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    std::vector<std::string> converted {};
    converted.reserve(texts.size());

    for (const std::string_view sv : texts)
    {
        converted.emplace_back(sv);
    }

    return frequency(converted);
}

}  // namespace parallel_letter_frequency
