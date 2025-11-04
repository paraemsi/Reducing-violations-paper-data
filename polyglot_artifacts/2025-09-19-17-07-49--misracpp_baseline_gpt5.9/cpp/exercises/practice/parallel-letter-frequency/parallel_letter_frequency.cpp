#include "parallel_letter_frequency.h"

#include <array>
#include <cctype>
#include <thread>
#include <vector>
#include <string_view>

namespace parallel_letter_frequency {

frequency_map frequency(const std::vector<std::string_view>& texts) {
    if (texts.empty()) {
        return {};
    }

    const unsigned int hc = std::thread::hardware_concurrency();
    const std::size_t threads = std::min<std::size_t>(texts.size(), hc ? hc : 2u);

    std::vector<std::array<unsigned int, 26>> partials(threads);
    for (auto& arr : partials) {
        arr.fill(0);
    }

    auto worker = [&](std::size_t begin, std::size_t end, std::size_t slot) {
        auto& counts = partials[slot];
        for (std::size_t i = begin; i < end; ++i) {
            const std::string_view s = texts[i];
            for (unsigned char uc : s) {
                if (std::isalpha(uc)) {
                    unsigned char lower = static_cast<unsigned char>(std::tolower(uc));
                    if (lower >= 'a' && lower <= 'z') {
                        counts[lower - 'a']++;
                    }
                }
            }
        }
    };

    std::vector<std::thread> ts;
    ts.reserve(threads);

    auto chunk_start = [&](std::size_t t) {
        return t * texts.size() / threads;
    };

    for (std::size_t t = 0; t < threads; ++t) {
        std::size_t begin = chunk_start(t);
        std::size_t end = chunk_start(t + 1);
        ts.emplace_back(worker, begin, end, t);
    }

    for (auto& th : ts) {
        th.join();
    }

    std::array<unsigned int, 26> total{};
    total.fill(0);
    for (const auto& arr : partials) {
        for (std::size_t i = 0; i < 26; ++i) {
            total[i] += arr[i];
        }
    }

    frequency_map result;
    for (std::size_t i = 0; i < 26; ++i) {
        if (total[i] != 0) {
            result[static_cast<char>('a' + i)] = static_cast<int>(total[i]);
        }
    }

    return result;
}

frequency_map frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

}
