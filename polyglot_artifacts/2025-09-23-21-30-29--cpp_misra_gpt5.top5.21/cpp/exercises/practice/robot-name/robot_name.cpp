#include "robot_name.h"

#include <unordered_set>
#include <random>
#include <mutex>
#include <string>
#include <cstdint>

namespace robot_name {

namespace {

auto get_rng() -> std::mt19937& {
    thread_local std::mt19937 rng{std::random_device{}()};
    return rng;
}

auto generate_random_name() -> std::string {
    static const std::string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    static const std::string digits = "0123456789";
    static constexpr std::uint32_t letters_count = 26U;
    static constexpr std::uint32_t digits_count = 10U;

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, (letters_count - 1U));
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, (digits_count - 1U));

    std::string result;
    result.reserve(5U);

    std::uint32_t idx = letter_dist(get_rng());
    result.push_back(letters[static_cast<std::size_t>(idx)]);
    idx = letter_dist(get_rng());
    result.push_back(letters[static_cast<std::size_t>(idx)]);

    idx = digit_dist(get_rng());
    result.push_back(digits[static_cast<std::size_t>(idx)]);
    idx = digit_dist(get_rng());
    result.push_back(digits[static_cast<std::size_t>(idx)]);
    idx = digit_dist(get_rng());
    result.push_back(digits[static_cast<std::size_t>(idx)]);

    return result;
}

auto used_names() -> std::unordered_set<std::string>& {
    static std::unordered_set<std::string> set{};
    return set;
}

auto used_names_mutex() -> std::mutex& {
    static std::mutex m{};
    return m;
}

}  // namespace

auto robot::generate_unique_name() -> std::string {
    for (;;) {
        std::string candidate = generate_random_name();
        {
            std::lock_guard<std::mutex> lock(used_names_mutex());
            auto inserted = used_names().insert(candidate);
            if (inserted.second) {
                return candidate;
            }
        }
    }
}

robot::robot()
    : m_name(generate_unique_name()) {
}

auto robot::name() const -> std::string {
    return m_name;
}

void robot::reset() {
    m_name = generate_unique_name();
}

}  // namespace robot_name
