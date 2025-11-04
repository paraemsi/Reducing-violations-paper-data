#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <execution>
#include <mutex>
#include <locale>
#include <string_view>

namespace parallel_letter_frequency {

count_map frequency(const std::vector<std::string_view>& texts)
{
    count_map global_counts {};
    std::mutex merge_mutex {};

    const auto worker =
        [&global_counts, &merge_mutex](const std::string_view& text) noexcept
        {
            count_map local_counts {};
            static constexpr std::string_view alphabet { "abcdefghijklmnopqrstuvwxyz" };

            static const std::locale loc {};
            for (char ch : text)
            {
                char lower_ch = std::tolower(ch, loc);

                for (char letter : alphabet)
                {
                    if (lower_ch == letter)
                    {
                        ++local_counts[letter];
                        break;
                    }
                }
            }

            {
                std::lock_guard<std::mutex> guard { merge_mutex };
                for (const auto& kv : local_counts)
                {
                    global_counts[kv.first] += kv.second;
                }
            }
        };

    std::for_each(std::execution::par, texts.begin(), texts.end(), worker);

    return global_counts;
}

}   // namespace parallel_letter_frequency
