#include "parallel_letter_frequency.h"

#include <thread>
#include <locale>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    const auto worker = [](std::string_view text) -> frequency_map
    {
        const std::locale loc{};
        frequency_map local_counts{};

        for (const char raw_ch : text)
        {
            /* convert character to lower-case using locale */
            const char ch = static_cast<char>(std::tolower(raw_ch, loc));

            if (std::isalpha(ch, loc) != 0)
            {
                (void)++local_counts[ch];
            }
        }

        return local_counts;
    };

    std::vector<std::thread> threads{};
    std::vector<frequency_map> partial_results(texts.size());

    for (std::size_t idx = std::size_t{0}; idx < texts.size(); ++idx)
    {
        threads.emplace_back(
            [&partial_results, &texts, idx, &worker]()
            {
                partial_results[idx] = worker(texts[idx]);
            });
    }

    for (std::thread& thr : threads)
    {
        if (thr.joinable())
        {
            thr.join();
        }
    }

    frequency_map result{};

    for (const frequency_map& part : partial_results)
    {
        for (const auto& kv : part)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

} // namespace parallel_letter_frequency
