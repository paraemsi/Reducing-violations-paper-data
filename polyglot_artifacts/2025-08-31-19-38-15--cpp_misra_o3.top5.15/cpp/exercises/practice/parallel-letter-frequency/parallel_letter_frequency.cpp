#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cstddef>           // for std::size_t
#include <string>
#include <string_view>
#include <thread>
#include <utility>
#include <map>

namespace parallel_letter_frequency {

 //------------------------------------------------------------
 //  Helpers
 //------------------------------------------------------------

namespace
{
    using traits = std::char_traits<char>;

    inline auto is_letter(const char ch) -> bool
    {
        const auto code{ traits::to_int_type(ch) };
        const auto lower_a{ traits::to_int_type('a') };
        const auto lower_z{ traits::to_int_type('z') };
        const auto upper_a{ traits::to_int_type('A') };
        const auto upper_z{ traits::to_int_type('Z') };

        return ((code >= lower_a) && (code <= lower_z)) ||
               ((code >= upper_a) && (code <= upper_z));
    }

    inline auto to_lower(const char ch) -> char
    {
        auto code{ traits::to_int_type(ch) };
        const auto upper_a{ traits::to_int_type('A') };
        const auto upper_z{ traits::to_int_type('Z') };

        if ((code >= upper_a) && (code <= upper_z))
        {
            code = code + (traits::to_int_type('a') - upper_a);
        }

        return traits::to_char_type(code);
    }
}
static auto count_letters_single(std::string_view text) -> frequency_map
{
    frequency_map local{};

    for (const char ch : text)
    {
        if (is_letter(ch))
        {
            const char lower_char{ to_lower(ch) };
            ++local[lower_char];
        }
    }

    return local;
}

//------------------------------------------------------------
//  Public API
//------------------------------------------------------------
template <typename TextContainer>
static auto frequency_impl(const TextContainer& texts) -> frequency_map
{
    if (texts.empty())
    {
        return frequency_map{};
    }

    const std::size_t hw_threads{ std::thread::hardware_concurrency() };
    const std::size_t max_threads{ (hw_threads == 0U) ? 2U : hw_threads };
    const std::size_t thread_count{
        (texts.size() < max_threads) ? texts.size() : max_threads
    };

    const std::size_t block_size{
        (texts.size() + thread_count - 1U) / thread_count
    };

    std::vector<std::thread> workers{};
    workers.reserve(thread_count);

    std::vector<frequency_map> partial_results(thread_count);

    auto worker = [&texts](frequency_map& dest,
                           std::size_t begin_idx,
                           std::size_t end_idx) -> void
    {
        for (std::size_t idx{ begin_idx }; idx < end_idx; ++idx)
        {
            const frequency_map local{ count_letters_single(texts[idx]) };
            for (const auto& kv : local)
            {
                dest[kv.first] += kv.second;
            }
        }
    };

    for (std::size_t t{ 0U }; t < thread_count; ++t)
    {
        const std::size_t begin{ t * block_size };
        const std::size_t end{ (begin + block_size < texts.size())
                                   ? (begin + block_size)
                                   : texts.size() };

        workers.emplace_back(worker,
                             std::ref(partial_results[t]),
                             begin,
                             end);
    }

    for (std::thread& th : workers)
    {
        if (th.joinable())
        {
            th.join();
        }
    }

    frequency_map result{};
    for (const auto& part : partial_results)
    {
        for (const auto& kv : part)
        {
            result[kv.first] += kv.second;
        }
    }

    return result;
}

auto frequency(const std::vector<std::string>& texts) -> frequency_map
{
    return frequency_impl(texts);
}

auto frequency(const std::vector<std::string_view>& texts) -> frequency_map
{
    return frequency_impl(texts);
}

}   // namespace parallel_letter_frequency
