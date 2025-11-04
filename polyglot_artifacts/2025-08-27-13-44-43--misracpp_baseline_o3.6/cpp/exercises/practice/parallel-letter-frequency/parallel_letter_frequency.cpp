#include "parallel_letter_frequency.h"
#include <array>
#include <thread>
#include <cctype>
#include <algorithm>
#include <string_view>

namespace parallel_letter_frequency {

namespace {

template <typename StringLike>
std::map<char, int> frequency_generic(const std::vector<StringLike>& texts) {
    if (texts.empty()) {
        return {};
    }

    const std::size_t hardware_threads =
        std::thread::hardware_concurrency() ? std::thread::hardware_concurrency() : 2u;
    const std::size_t num_threads = std::min<std::size_t>(hardware_threads, texts.size());

    std::vector<std::array<int, 26>> partials(num_threads);
    for (auto& a : partials) {
        a.fill(0);
    }

    auto worker = [&](std::size_t thread_index, std::size_t begin, std::size_t end) {
        auto& local = partials[thread_index];
        for (std::size_t i = begin; i < end; ++i) {
            for (char ch : texts[i]) {
                unsigned char uch = static_cast<unsigned char>(ch);
                if (std::isalpha(uch)) {
                    uch = static_cast<unsigned char>(std::tolower(uch));
                    if (uch >= 'a' && uch <= 'z') {
                        local[uch - 'a']++;
                    }
                }
            }
        }
    };

    std::vector<std::thread> threads;
    const std::size_t block_size = texts.size() / num_threads;
    std::size_t start = 0;
    for (std::size_t t = 0; t < num_threads; ++t) {
        std::size_t end = (t == num_threads - 1) ? texts.size() : start + block_size;
        threads.emplace_back(worker, t, start, end);
        start = end;
    }

    for (auto& th : threads) {
        th.join();
    }

    std::array<int, 26> combined{};
    combined.fill(0);
    for (const auto& arr : partials) {
        for (std::size_t i = 0; i < 26; ++i) {
            combined[i] += arr[i];
        }
    }

    std::map<char, int> result;
    for (std::size_t i = 0; i < 26; ++i) {
        if (combined[i] > 0) {
            result[static_cast<char>('a' + i)] = combined[i];
        }
    }

    return result;
}

}  // unnamed namespace

std::map<char, int> frequency(const std::vector<std::string>& texts) {
    return frequency_generic(texts);
}

std::map<char, int> frequency(const std::vector<std::string_view>& texts) {
    return frequency_generic(texts);
}

}
