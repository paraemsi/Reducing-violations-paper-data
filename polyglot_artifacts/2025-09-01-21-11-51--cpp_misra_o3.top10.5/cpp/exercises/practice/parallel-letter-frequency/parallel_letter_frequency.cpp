#include "parallel_letter_frequency.h"

#include <future>
#include <locale>
#include <string>
#include <string_view>
#include <thread>
#include <unordered_map>
#include <vector>

namespace parallel_letter_frequency {

namespace {
/* Helper – count letters in a single text */
auto count_letters_in_text(std::string_view text) -> frequency_map
{
    frequency_map local_result{};
    const std::locale loc{};
    const std::string letters{"abcdefghijklmnopqrstuvwxyz"};

    for (const char ch : text)
    {
        const char lower{static_cast<char>(std::tolower(ch, loc))};

        /* Using std::string::find avoids relational / arithmetic
           operations on character values (MISRA compliant). */
        if (letters.find(lower) != std::string::npos)
        {
            ++local_result[lower];
        }
    }
    return local_result;
}
}  // unnamed namespace

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    /* Launch one task per input string – simple yet effective for the
       typical Exercism workloads. */
    std::vector<std::future<frequency_map>> tasks{};
    tasks.reserve(texts.size());

    for (const std::string_view& txt : texts)
    {
        tasks.emplace_back(std::async(
            std::launch::async,
            [txt]() -> frequency_map { return count_letters_in_text(txt); }));
    }

    frequency_map total{};

    for (auto& task : tasks)
    {
        const frequency_map part{task.get()};  // wait & obtain result
        for (const auto& kv : part)
        {
            total[kv.first] += kv.second;
        }
    }
    return total;
}

}  // namespace parallel_letter_frequency
