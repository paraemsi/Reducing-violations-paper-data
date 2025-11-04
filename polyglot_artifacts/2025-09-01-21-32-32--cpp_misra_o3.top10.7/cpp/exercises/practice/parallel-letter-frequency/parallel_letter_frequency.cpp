#include "parallel_letter_frequency.h"

#include <future>
#include <locale>
#include <string_view>

namespace parallel_letter_frequency {

namespace {

/*  Count letters in a single text.
    The helper is kept in an unnamed namespace to give it
    internal linkage and avoid polluting the public interface. */
auto count_letters(const std::string_view text,
                   const std::locale&        loc) -> frequency_map
{
    frequency_map local_counts{};

    for (const char ch : text)
    {
        /* Classification via <locale>; no direct numeric operations
           on the character value are performed. */
        if ((std::isalpha(ch, loc) != 0))
        {
            const char lower_ch{static_cast<char>(std::tolower(ch, loc))};
            ++local_counts[lower_ch];
        }
    }

    return local_counts;
}

}   // unnamed namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    const std::locale                    loc{};
    std::vector<std::future<frequency_map>> tasks{};
    tasks.reserve(texts.size());

    /*  Launch one asynchronous task per input string.
        Using std::launch::async guarantees a new thread or a thread
        from the implementation’s pool. */
    for (const std::string_view& txt : texts)
    {
        tasks.emplace_back(
            std::async(std::launch::async, count_letters, std::string_view{txt}, std::cref(loc)));
    }

    frequency_map result{};

    /*  Collect the partial maps and merge them into the final result. */
    for (auto& fut : tasks)
    {
        const frequency_map partial{fut.get()};

        for (const auto& kv : partial)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

}   // namespace parallel_letter_frequency
