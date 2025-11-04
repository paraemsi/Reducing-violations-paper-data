#include "robot_name.h"

#include <array>
#include <random>
#include <set>
#include <cstdint>

namespace robot_name {

namespace {

// Set to keep track of names that are already in use.
static std::set<std::string> g_used_names;

// Helper to build a random candidate name (may collide).
static std::string generate_random_name(std::mt19937& rng)
{
    static constexpr std::array<char, 26U> letters{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };

    static constexpr std::array<char, 10U> digits{
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string candidate;
    candidate.reserve(5U);

    candidate.push_back(letters[letter_dist(rng)]);
    candidate.push_back(letters[letter_dist(rng)]);

    for (std::uint32_t i{0U}; i < 3U; ++i)
    {
        candidate.push_back(digits[digit_dist(rng)]);
    }

    return candidate;
}

} // unnamed namespace

robot::robot() : m_name()
{
}

std::mt19937& robot::generator()
{
    static std::mt19937 rng{std::random_device{}()};
    return rng;
}

std::string robot::generate_unique_name()
{
    std::string candidate{};
    auto& rng = generator();

    // Keep generating until a unique name is found.
    do
    {
        candidate = generate_random_name(rng);
    }
    while ((g_used_names.insert(candidate)).second == false);

    return candidate;
}

const std::string& robot::name()
{
    if (m_name.empty())
    {
        m_name = generate_unique_name();
    }

    return m_name;
}

void robot::reset()
{
    if (!m_name.empty())
    {
        (void)g_used_names.erase(m_name);
        m_name.clear();
    }
}

} // namespace robot_name
