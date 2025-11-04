#include "robot_name.h"

#include <array>
#include <random>
#include <string>
#include <unordered_set>
#include <cstddef>

namespace {
    // Allowed character tables (no arithmetic on character values)
    constexpr std::array<char, 26U> LETTERS{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    constexpr std::array<char, 10U> DIGITS{
        '0','1','2','3','4','5','6','7','8','9'
    };

    // Random engine seeded once
    std::mt19937& engine() {
        static std::mt19937 eng{std::random_device{}()};
        return eng;
    }

    // Global set of names to ensure uniqueness across the factory lifetime
    std::unordered_set<std::string> used_names{};
}  // namespace

namespace robot_name {

robot::robot() = default;

std::string robot::make_random_name() {
    std::string s{};
    s.reserve(5U);

    const std::size_t li1 = std::uniform_int_distribution<std::size_t>(
        static_cast<std::size_t>(0), (LETTERS.size() - static_cast<std::size_t>(1)))(engine());
    const std::size_t li2 = std::uniform_int_distribution<std::size_t>(
        static_cast<std::size_t>(0), (LETTERS.size() - static_cast<std::size_t>(1)))(engine());
    const std::size_t di1 = std::uniform_int_distribution<std::size_t>(
        static_cast<std::size_t>(0), (DIGITS.size() - static_cast<std::size_t>(1)))(engine());
    const std::size_t di2 = std::uniform_int_distribution<std::size_t>(
        static_cast<std::size_t>(0), (DIGITS.size() - static_cast<std::size_t>(1)))(engine());
    const std::size_t di3 = std::uniform_int_distribution<std::size_t>(
        static_cast<std::size_t>(0), (DIGITS.size() - static_cast<std::size_t>(1)))(engine());

    s.push_back(LETTERS.at(li1));
    s.push_back(LETTERS.at(li2));
    s.push_back(DIGITS.at(di1));
    s.push_back(DIGITS.at(di2));
    s.push_back(DIGITS.at(di3));

    return s;
}

std::string robot::allocate_unique_name() {
    for (;;) {
        std::string candidate = make_random_name();
        const auto insert_result = used_names.insert(candidate);
        if (insert_result.second) {
            return candidate;
        }
    }
}

std::string robot::name() const {
    if (m_name.empty()) {
        m_name = allocate_unique_name();
    }
    return m_name;
}

void robot::reset() {
    if (!m_name.empty()) {
        // Do not release the previous name back into the pool to avoid reuse
        m_name.clear();
    }
}

}  // namespace robot_name
