#include "parallel_letter_frequency.h"
#include <algorithm>
#include <cctype>
#include <future>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

namespace {

/* Compute the frequency map for a single text string. */
frequency_map compute_single(const std::string& text)
{
    frequency_map local_result {};

    for (char const ch : text)
    {
        /* convert to lower case – explicit cast to unsigned char avoids UB */
        char const lower_ch = static_cast<char>(
            std::tolower(static_cast<unsigned char>(ch)));

        /* keep ASCII letters only – use std::char_traits to compare
         * without treating the character object itself numerically
         * (MISRA: “The numerical value of a character shall not be used”). */
        auto const int_lower =
            std::char_traits<char>::to_int_type(lower_ch);
        auto const int_a =
            std::char_traits<char>::to_int_type('a');
        auto const int_z =
            std::char_traits<char>::to_int_type('z');

        if ((int_lower >= int_a) && (int_lower <= int_z))
        {
            ++local_result[lower_ch];
        }
    }

    return local_result;
}

/* Merge one map into another (add counts). */
void merge_into(frequency_map& destination,
                frequency_map const& source)
{
    for (auto const& [key, value] : source)
    {
        destination[key] += value;
    }
}

} // unnamed namespace

frequency_map frequency(const std::vector<std::string>& texts)
{
    /* early-out on empty input */
    if (texts.empty())
    {
        return {};
    }

    std::size_t const hardware_threads =
        (std::thread::hardware_concurrency() == 0U)
            ? 2U
            : static_cast<std::size_t>(std::thread::hardware_concurrency());

    std::size_t const wanted_threads =
        (texts.size() < hardware_threads) ? texts.size() : hardware_threads;

    /* launch asynchronous tasks */
    std::vector<std::future<frequency_map>> futures {};
    futures.reserve(wanted_threads);

    /* simple round-robin partitioning */
    for (std::size_t t {0U}; t < wanted_threads; ++t)
    {
        futures.emplace_back(std::async(std::launch::async,
                                        [&texts, t, wanted_threads]() {
                                            frequency_map local_acc {};

                                            for (std::size_t i {t};
                                                 i < texts.size();
                                                 i += wanted_threads)
                                            {
                                                merge_into(local_acc,
                                                           compute_single(texts[i]));
                                            }
                                            return local_acc;
                                        }));
    }

    /* collect and merge results */
    frequency_map result {};
    for (auto& fut : futures)
    {
        merge_into(result, fut.get());
    }

    return result;
}

} // namespace parallel_letter_frequency
