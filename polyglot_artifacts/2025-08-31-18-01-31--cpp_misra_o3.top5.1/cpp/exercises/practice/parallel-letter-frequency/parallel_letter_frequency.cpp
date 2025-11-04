#include "parallel_letter_frequency.h"

#include <algorithm>
#include <execution>
#include <locale>
#include <mutex>
#include <string_view>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    static const std::string_view alphabet{"abcdefghijklmnopqrstuvwxyz"};

    frequency_map result{};
    std::mutex result_mutex{};

    std::for_each(std::execution::par, texts.begin(), texts.end(),
        [&result, &result_mutex](const std::string_view text)
        {
            frequency_map local{};
            const std::locale loc{};

            for (const char ch : text)
            {
                /* Explicit cast for MISRA-compliant conversion */
                const char lower = static_cast<char>(std::tolower(ch, loc));

                if (std::find(alphabet.begin(), alphabet.end(), lower) != alphabet.end())
                {
                    ++local[lower];
                }
            }

            {
                std::lock_guard<std::mutex> lock(result_mutex);
                for (const auto& kv : local)
                {
                    result[kv.first] += kv.second;
                }
            }
        });

    return result;
}

}
