#include "parallel_letter_frequency.h"

#include <future>
#include <utility>
#include <string_view>

namespace parallel_letter_frequency {

namespace {

/*
 * Count the letters that appear in a single text.
 * The helper is kept in an unnamed namespace as it is an
 * implementation detail.
 */
auto count_letters(std::string_view text, const std::locale& loc)
    -> frequency_map
{
    frequency_map local_counts{};

    for (const char ch : text)
    {
        if ((std::isalpha(ch, loc) != 0))
        {
            const char lower_ch{ static_cast<char>(std::tolower(ch, loc)) };
            ++local_counts[lower_ch];
        }
    }

    return local_counts;
}

}  // unnamed namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    const std::locale loc{};  // default locale in use

    /* One asynchronous task per input string. */
    std::vector<std::future<frequency_map>> tasks{};
    tasks.reserve(texts.size());

    for (const std::string_view text : texts)
    {
        tasks.emplace_back(
            std::async(std::launch::async,
                       [loc, text]() -> frequency_map
                       {
                           return count_letters(text, loc);
                       }));
    }

    /* Aggregate the results from all tasks. */
    frequency_map global_counts{};

    for (std::future<frequency_map>& task : tasks)
    {
        const frequency_map local_counts{ task.get() };
        for (const auto& kv : local_counts)
        {
            global_counts[kv.first] += kv.second;
        }
    }

    return global_counts;
}

}  // namespace parallel_letter_frequency
