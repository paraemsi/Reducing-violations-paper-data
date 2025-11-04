#include "parallel_letter_frequency.h"

#include <algorithm>
#include <cctype>
#include <future>
#include <thread>
#include <unordered_map>

namespace parallel_letter_frequency {

// helper that does the counting work on a sub-range of the input vector
static frequency_map count_range(const std::vector<std::string_view>& input,
                                 std::size_t begin, std::size_t end) {
    std::unordered_map<char, int> local;  // use unordered_map for speed

    for (std::size_t i = begin; i < end; ++i) {
        for (unsigned char ch : input[i]) {
            if (std::isalpha(ch)) {
                ch = static_cast<unsigned char>(std::tolower(ch));
                ++local[static_cast<char>(ch)];
            }
        }
    }

    // move into ordered map for deterministic result ordering
    return frequency_map{local.begin(), local.end()};
}

frequency_map frequency(const std::vector<std::string_view>& input) {
    return frequency(input, std::thread::hardware_concurrency());
}

frequency_map frequency(const std::vector<std::string_view>& input, std::size_t workers) {
    if (input.empty()) {
        return {};
    }

    std::size_t hardware = std::thread::hardware_concurrency();
    if (workers == 0) {
        workers = (hardware == 0 ? 2 : hardware);
    }
    workers = std::min(workers, input.size());
    if (workers == 0) {
        workers = 1;
    }

    std::vector<std::future<frequency_map>> futures;
    futures.reserve(workers);

    std::size_t block_size = input.size() / workers;
    std::size_t remainder  = input.size() % workers;
    std::size_t begin = 0;

    for (std::size_t w = 0; w < workers; ++w) {
        std::size_t end = begin + block_size + (w < remainder ? 1 : 0);

        futures.emplace_back(std::async(std::launch::async,
                                        count_range,
                                        std::cref(input), begin, end));
        begin = end;
    }

    frequency_map result;
    for (auto& fut : futures) {
        frequency_map local = fut.get();
        for (const auto& [ch, cnt] : local) {
            result[ch] += cnt;
        }
    }
    return result;
}

} // namespace parallel_letter_frequency
