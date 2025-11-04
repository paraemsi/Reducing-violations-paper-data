#include "parallel_letter_frequency.h"
#include <algorithm>
#include <cctype>
#include <map>
#include <string>
#include <string_view>
#include <thread>
#include <vector>

namespace parallel_letter_frequency {

namespace {

// Implementation shared by both overloads.
template <typename String>
std::map<char, int> frequency_impl(const std::vector<String>& texts)
{
    std::map<char, int> global_counts;

    if (texts.empty())
        return global_counts;

    const std::size_t hw_threads  = std::thread::hardware_concurrency();
    const std::size_t max_threads = hw_threads == 0 ? 2 : hw_threads;
    const std::size_t thread_count =
        std::min<std::size_t>(max_threads, texts.size());

    std::vector<std::map<char, int>> partial_counts(thread_count);
    std::vector<std::thread>        workers(thread_count);

    auto worker = [&](std::size_t tid, std::size_t begin, std::size_t end) {
        auto& local = partial_counts[tid];
        for (std::size_t i = begin; i < end; ++i) {
            for (unsigned char ch : texts[i]) {
                if (std::isalpha(static_cast<unsigned char>(ch))) {
                    char lower = static_cast<char>(
                        std::tolower(static_cast<unsigned char>(ch)));
                    ++local[lower];
                }
            }
        }
    };

    // Divide the work as evenly as possible.
    const std::size_t chunk_size = texts.size() / thread_count;
    const std::size_t remainder  = texts.size() % thread_count;

    std::size_t begin = 0;
    for (std::size_t t = 0; t < thread_count; ++t) {
        std::size_t end = begin + chunk_size + (t < remainder ? 1 : 0);
        workers[t]      = std::thread(worker, t, begin, end);
        begin           = end;
    }

    for (auto& th : workers)
        th.join();

    // Merge the individual thread results.
    for (const auto& local : partial_counts) {
        for (const auto& [ch, cnt] : local)
            global_counts[ch] += cnt;
    }

    return global_counts;
}

} // namespace

std::map<char, int> frequency(const std::vector<std::string>& texts)
{
    return frequency_impl(texts);
}

std::map<char, int> frequency(const std::vector<std::string_view>& texts)
{
    return frequency_impl(texts);
}

}
