#include "robot_name.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace {

constexpr std::array<char, 26U> LETTERS = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

constexpr std::array<char, 10U> DIGITS = {'0','1','2','3','4','5','6','7','8','9'};

std::unordered_set<std::string> s_used{};
std::mutex s_mutex{};

inline std::mt19937& rng()
{
    static thread_local std::mt19937 gen{std::random_device{}()};
    return gen;
}

}  // unnamed namespace

namespace robot_name {

std::string robot::generate_name_unchecked()
{
    std::string result{};
    result.reserve(5U);

    static thread_local std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    static thread_local std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    {
        const std::uint32_t i0 = letter_dist(rng());
        result.push_back(LETTERS[static_cast<std::size_t>(i0)]);
    }
    {
        const std::uint32_t i1 = letter_dist(rng());
        result.push_back(LETTERS[static_cast<std::size_t>(i1)]);
    }
    {
        const std::uint32_t d0 = digit_dist(rng());
        result.push_back(DIGITS[static_cast<std::size_t>(d0)]);
    }
    {
        const std::uint32_t d1 = digit_dist(rng());
        result.push_back(DIGITS[static_cast<std::size_t>(d1)]);
    }
    {
        const std::uint32_t d2 = digit_dist(rng());
        result.push_back(DIGITS[static_cast<std::size_t>(d2)]);
    }

    return result;
}

std::string robot::generate_unique_name()
{
    for (;;) {
        const std::string candidate = robot::generate_name_unchecked();

        std::unique_lock<std::mutex> lock(s_mutex);
        const auto insert_result = s_used.insert(candidate);
        if (insert_result.second) {
            return candidate;
        }
    }
}

robot::robot()
    : m_name(generate_unique_name())
{
}

std::string robot::name() const
{
    return m_name;
}

void robot::reset()
{
    m_name = generate_unique_name();
}

}  // namespace robot_name
