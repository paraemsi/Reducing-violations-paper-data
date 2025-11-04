#include "parallel_letter_frequency.h"
#include <future>
#include <locale>
#include <string_view>
#include <cctype>

namespace parallel_letter_frequency {

namespace
{

    // Count letters in a single text, case-insensitively.
    static std::map<char, std::uint32_t> count_text(const std::string_view& text)
    {
        static const std::string_view letters{"abcdefghijklmnopqrstuvwxyz"};
        const std::locale loc{};
        std::map<char, std::uint32_t> counts{};

        for (const char ch : text)
        {
            const char lower{std::tolower(ch, loc)};
            if (letters.find(lower) != std::string_view::npos)
            {
                ++counts[lower];
            }
        }

        return counts;
    }

} // unnamed namespace

std::map<char, std::uint32_t> frequency(const std::vector<std::string_view>& texts)
{
    std::vector<std::future<std::map<char, std::uint32_t>>> futures{};
    futures.reserve(texts.size());

    for (const std::string_view txt : texts)
    {
        futures.emplace_back(std::async(std::launch::async, count_text, txt));
    }

    std::map<char, std::uint32_t> total{};

    for (auto& fut : futures)
    {
        const std::map<char, std::uint32_t> part{fut.get()};
        for (const auto& entry : part)
        {
            total[entry.first] += entry.second;
        }
    }

    return total;
}

}
