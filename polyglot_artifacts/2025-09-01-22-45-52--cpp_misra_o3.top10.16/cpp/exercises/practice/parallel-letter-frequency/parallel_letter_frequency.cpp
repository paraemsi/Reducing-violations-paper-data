#include "parallel_letter_frequency.h"

#include <future>
#include <locale>
#include <string_view>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    std::vector<std::future<frequency_map>> tasks{};
    tasks.reserve(texts.size());

    /*  Launch one asynchronous task per input string. */
    for (const std::string_view text : texts)
    {
        tasks.push_back(std::async(
            std::launch::async,
            [text]() -> frequency_map
            {
                const std::locale loc{};
                frequency_map     local_counts{};

                for (letter_t ch : text)
                {
                    const unsigned char uch = static_cast<unsigned char>(ch);

                    if ((std::isalpha(uch, loc) != 0))
                    {
                        const letter_t lower_ch =
                            static_cast<letter_t>(std::tolower(uch, loc));
                        ++local_counts[lower_ch];
                    }
                }

                return local_counts;
            }));
    }

    /*  Merge the individual maps into the final result. */
    frequency_map result{};

    for (std::future<frequency_map>& task : tasks)
    {
        const frequency_map local_counts = task.get();

        for (const auto& kv : local_counts)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
