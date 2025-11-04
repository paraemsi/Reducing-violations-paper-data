#include "parallel_letter_frequency.h"
#include <thread>
#include <locale>
#include <vector>
#include <unordered_map>
#include <string_view>

namespace parallel_letter_frequency {

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    if(texts.empty())
    {
        return frequency_map{};
    }

    std::uint32_t thread_count =
        static_cast<std::uint32_t>(std::thread::hardware_concurrency());
    if(thread_count == 0U)
    {
        thread_count = 1U;
    }

    if(static_cast<std::uint32_t>(texts.size()) < thread_count)
    {
        thread_count = static_cast<std::uint32_t>(texts.size());
    }

    std::vector<frequency_map> partial(thread_count);
    std::vector<std::thread> workers;
    if(thread_count > 1U)
    {
        workers.reserve(thread_count - 1U);
    }

    auto const worker =
        [&texts, &partial, thread_count](std::uint32_t index) -> void
    {
        std::locale const loc{};
        frequency_map       local{};

        for(std::size_t i = index; i < texts.size(); i += thread_count)
        {
            for(char ch : texts[i])
            {
                if(std::isalpha(ch, loc))
                {
                    char const lower{std::tolower(ch, loc)};
                    local[lower] += 1U;
                }
            }
        }

        partial[index] = std::move(local);
    };

    for(std::uint32_t idx = 1U; idx < thread_count; ++idx)
    {
        workers.emplace_back(worker, idx);
    }

    worker(0U);

    for(auto& th : workers)
    {
        th.join();
    }

    frequency_map result{};
    for(auto const& part : partial)
    {
        for(auto const& kv : part)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    std::vector<std::string_view> views{};
    views.reserve(texts.size());

    for(const std::string& s : texts)
    {
        views.emplace_back(s);
    }

    return frequency(views);
}

} // namespace parallel_letter_frequency
