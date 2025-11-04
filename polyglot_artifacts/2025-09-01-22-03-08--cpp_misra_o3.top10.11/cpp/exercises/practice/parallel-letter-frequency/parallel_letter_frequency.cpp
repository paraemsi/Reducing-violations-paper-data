#include "parallel_letter_frequency.h"

#include <algorithm>
#include <locale>
#include <mutex>
#include <cstddef>
#include <thread>
#include <string_view>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts)
{
    /*  Early return on empty input                                          */
    if (texts.empty())
    {
        return frequency_map{};
    }

    const std::uint32_t max_threads { std::thread::hardware_concurrency() };
    const std::uint32_t thread_count { (max_threads == static_cast<std::uint32_t>(0U))
                                           ? static_cast<std::uint32_t>(1U)
                                           : std::min(max_threads,
                                                      static_cast<std::uint32_t>(texts.size())) };
    const std::size_t thread_count_z { static_cast<std::size_t>(thread_count) };

    /*  Protects access to the shared result map                             */
    std::mutex                                           merge_mutex {};
    frequency_map                                        global_result {};
    std::vector<std::thread>                             workers {};
    workers.reserve(static_cast<std::size_t>(thread_count));

    /*  Partition the work: each thread processes every N-th string          */
    const std::locale                                     loc {};
    for (std::uint32_t tid { 0U }; tid < thread_count; ++tid)
    {
        workers.emplace_back(
            [&, tid]()
            {
                frequency_map local_result {};

                for (std::size_t idx { static_cast<std::size_t>(tid) }; idx < texts.size();
                     idx += thread_count_z)
                {
                    const std::string_view text_ref { texts.at(static_cast<std::size_t>(idx)) };

                    for (const char ch : text_ref)
                    {
                        const unsigned char uch { static_cast<unsigned char>(ch) };

                        if (std::isalpha(uch, loc) != false)
                        {
                            const char lower_ch {
                                static_cast<char>(std::tolower(uch, loc))
                            };
                            ++local_result[lower_ch];
                        }
                    }
                }

                /*  Merge this thread's partial result into the global map   */
                {
                    std::lock_guard<std::mutex> guard { merge_mutex };

                    for (const auto& pair_ref : local_result)
                    {
                        global_result[pair_ref.first] += pair_ref.second;
                    }
                }
            });
    }

    /*  Join all worker threads                                              */
    for (std::thread& t_ref : workers)
    {
        if (t_ref.joinable())
        {
            t_ref.join();
        }
    }

    return global_result;
}

/*  Overload forwarding std::string input to the std::string_view version    */
frequency_map frequency(const std::vector<std::string>& texts)
{
    std::vector<std::string_view> views {};
    views.reserve(texts.size());

    for (const std::string& s_ref : texts)
    {
        views.emplace_back(s_ref);
    }

    return frequency(views);
}

}   // namespace parallel_letter_frequency
