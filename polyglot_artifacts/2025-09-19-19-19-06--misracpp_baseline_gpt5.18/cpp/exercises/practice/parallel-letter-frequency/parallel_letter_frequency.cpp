#include "parallel_letter_frequency.h"

#include <array>
#include <cctype>
#include <thread>
#include <vector>
#include <algorithm>
#include <string_view>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    std::vector<std::string> copy;
    copy.reserve(texts.size());
    for (std::string_view sv : texts) {
        copy.emplace_back(sv);
    }
    return frequency(copy);
}

frequency_map frequency(const std::vector<const char*>& texts) {
    std::vector<std::string> copy;
    copy.reserve(texts.size());
    for (const char* s : texts) {
        copy.emplace_back(s ? s : "");
    }
    return frequency(copy);
}

frequency_map frequency(const std::vector<std::string>& texts) {
    if (texts.empty()) {
        return {};
    }

    const unsigned hw = std::thread::hardware_concurrency();
    std::size_t workers = hw ? static_cast<std::size_t>(hw) : 2u;
    workers = std::min<std::size_t>(workers, texts.size());
    if (workers == 0) {
        workers = 1;
    }

    const std::size_t chunk_size = (texts.size() + workers - 1) / workers;

    std::vector<std::array<int, 26>> partials(workers);
    for (auto& arr : partials) {
        arr.fill(0);
    }

    std::vector<std::thread> threads;
    threads.reserve(workers);

    for (std::size_t w = 0; w < workers; ++w) {
        const std::size_t begin = w * chunk_size;
        const std::size_t end = std::min(texts.size(), begin + chunk_size);
        if (begin >= end) {
            continue;  // No work assigned to this worker.
        }

        threads.emplace_back([begin, end, &texts, &partials, w]() {
            auto& counts = partials[w];
            for (std::size_t i = begin; i < end; ++i) {
                const std::string& s = texts[i];
                for (unsigned char ch : s) {
                    const unsigned char c = ch;
                    const char lower = static_cast<char>(std::tolower(c));
                    if (lower >= 'a' && lower <= 'z') {
                        counts[lower - 'a'] += 1;
                    }
                }
            }
        });
    }

    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    frequency_map result;
    for (const auto& arr : partials) {
        for (int idx = 0; idx < 26; ++idx) {
            const int count = arr[idx];
            if (count != 0) {
                const char letter = static_cast<char>('a' + idx);
                result[letter] += count;
            }
        }
    }

    return result;
}

}  // namespace parallel_letter_frequency
