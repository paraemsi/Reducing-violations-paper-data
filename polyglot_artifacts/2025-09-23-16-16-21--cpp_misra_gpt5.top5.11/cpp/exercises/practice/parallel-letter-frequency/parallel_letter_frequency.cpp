#include "parallel_letter_frequency.h"

#include <future>
#include <locale>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

namespace parallel_letter_frequency {

namespace {
auto local_frequency(std::string_view text) -> frequency_map
{
    const std::locale loc = std::locale::classic();
    frequency_map result{};

    for (const char_type ch : text)
    {
        if (std::isalpha(ch, loc))
        {
            const char_type lower = std::tolower(ch, loc);
            ++result[lower];
        }
    }

    return result;
}
}  // namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    std::vector<std::future<frequency_map>> tasks{};
    tasks.reserve(texts.size());

    for (const std::string_view s : texts)
    {
        tasks.emplace_back(std::async(std::launch::async, local_frequency, s));
    }

    frequency_map total{};

    for (auto& fut : tasks)
    {
        const frequency_map partial = fut.get();
        for (const auto& kv : partial)
        {
            total[kv.first] += kv.second;
        }
    }

    return total;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::future<frequency_map>> tasks{};
    tasks.reserve(texts.size());

    for (const std::string& s : texts)
    {
        const std::string_view sv{s};
        tasks.emplace_back(std::async(std::launch::async, local_frequency, sv));
    }

    frequency_map total{};

    for (auto& fut : tasks)
    {
        const frequency_map partial = fut.get();
        for (const auto& kv : partial)
        {
            total[kv.first] += kv.second;
        }
    }

    return total;
}

}  // namespace parallel_letter_frequency
