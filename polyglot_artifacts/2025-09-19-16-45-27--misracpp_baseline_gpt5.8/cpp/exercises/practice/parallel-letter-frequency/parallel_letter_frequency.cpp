#include "parallel_letter_frequency.h"

#include <array>
#include <cctype>
#include <thread>
#include <vector>
#include <algorithm>
#include <map>
#include <string>
#include <string_view>

namespace parallel_letter_frequency {

namespace {
// Count letters in a single string into counts array.
inline void count_in_text(std::string_view text, std::array<int, 26>& counts) {
    for (unsigned char ch : text) {
        unsigned char lower = static_cast<unsigned char>(std::tolower(ch));
        if (lower >= 'a' && lower <= 'z') {
            ++counts[static_cast<std::size_t>(lower - 'a')];
        }
    }
}
} // unnamed namespace

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    unsigned int hw = std::thread::hardware_concurrency();
    std::size_t workers = hw == 0 ? 1u : static_cast<std::size_t>(hw);
    return frequency(texts, workers);
}

std::map<char, int> frequency(const std::vector<std::string_view>& texts, std::size_t workers) {
    if (texts.empty()) {
        return {};
    }

    if (workers == 0) {
        workers = 1;
    }

    std::size_t actual_workers = std::min<std::size_t>(workers, texts.size());

    std::vector<std::array<int, 26>> local_counts(actual_workers);
    for (auto& arr : local_counts) {
        arr.fill(0);
    }

    auto worker_fn = [&](std::size_t idx) {
        for (std::size_t i = idx; i < texts.size(); i += actual_workers) {
            count_in_text(texts[i], local_counts[idx]);
        }
    };

    std::vector<std::thread> threads;
    threads.reserve(actual_workers);
    for (std::size_t i = 0; i < actual_workers; ++i) {
        threads.emplace_back(worker_fn, i);
    }
    for (auto& t : threads) {
        t.join();
    }

    std::array<int, 26> total{};
    total.fill(0);
    for (const auto& lc : local_counts) {
        for (std::size_t i = 0; i < 26; ++i) {
            total[i] += lc[i];
        }
    }

    std::map<char, int> result;
    for (std::size_t i = 0; i < 26; ++i) {
        if (total[i] > 0) {
            result.emplace(static_cast<char>('a' + i), total[i]);
        }
    }

    return result;
}

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views);
}

std::map<char, int> frequency(const std::vector<std::string>& texts, std::size_t workers) {
    std::vector<std::string_view> views;
    views.reserve(texts.size());
    for (const auto& s : texts) {
        views.emplace_back(s);
    }
    return frequency(views, workers);
}

}
