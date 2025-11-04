#include "parallel_letter_frequency.h"

#include <array>
#include <cctype>
#include <mutex>
#include <thread>
#include <cstdint>
#include <string_view>

namespace parallel_letter_frequency {

std::map<char, int> frequency(const std::vector<std::string_view>& input_texts)
{
    /* Use an array for the 26 letters; shared result protected by mutex. */
    std::array<std::int32_t, 26U> global_counts { };

    std::mutex                                    counts_mutex;
    auto worker = [&global_counts, &counts_mutex](std::string_view text) {
        std::array<std::int32_t, 26U> local_counts { };

        for (char ch : text) {
            /* Only letters are counted; classification via <cctype>. */
            if (std::isalpha(static_cast<unsigned char>(ch)) != 0) {
                char lower_char =
                    static_cast<char>(std::tolower(static_cast<unsigned char>(ch)));
                std::size_t index = static_cast<std::size_t>(
                    std::char_traits<char>::to_int_type(lower_char) -
                    std::char_traits<char>::to_int_type('a'));
                local_counts[index] += 1;
            }
        }

        {
            std::lock_guard<std::mutex> lock(counts_mutex);
            for (std::size_t i {0U}; i < 26U; ++i) {
                global_counts[i] += local_counts[i];
            }
        }
    };

    /* Launch one thread per input text. */
    std::vector<std::thread> threads;
    threads.reserve(input_texts.size());
    for (std::string_view text : input_texts) {
        threads.emplace_back(worker, text);
    }

    for (std::thread& th : threads) {
        if (th.joinable()) {
            th.join();
        }
    }

    /* Convert the array into the requested result map. */
    std::map<char, int> result;
    for (std::size_t i {0U}; i < 26U; ++i) {
        if (global_counts[i] != 0) {
            char letter = static_cast<char>(
                std::char_traits<char>::to_int_type('a') + static_cast<int>(i));
            result[letter] = static_cast<int>(global_counts[i]);
        }
    }

    return result;
}

}   // namespace parallel_letter_frequency
