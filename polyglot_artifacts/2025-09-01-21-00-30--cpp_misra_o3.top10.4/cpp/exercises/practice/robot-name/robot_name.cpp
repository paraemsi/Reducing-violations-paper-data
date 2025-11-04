#include "robot_name.h"

#include <array>
#include <cstddef>
#include <random>
#include <unordered_set>

namespace {

std::mt19937& rng()
{
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

std::unordered_set<std::string>& assigned_names()
{
    static std::unordered_set<std::string> names{};
    return names;
}

constexpr std::array<char, 26U> letters{
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
};

constexpr std::array<char, 10U> digits{
    '0','1','2','3','4','5','6','7','8','9'
};

}  // unnamed namespace

namespace robot_name {

Robot::~Robot()
{
    if(!m_name.empty())
    {
        (void)assigned_names().erase(m_name);
    }
}

const std::string& Robot::name() const
{
    if(m_name.empty())
    {
        m_name = generate_unique_name();
        (void)assigned_names().insert(m_name);
    }
    return m_name;
}

void Robot::reset()
{
    if(!m_name.empty())
    {
        (void)assigned_names().erase(m_name);
        m_name.clear();
    }
}

std::string Robot::generate_unique_name()
{
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string candidate{};
    candidate.reserve(5U);

    do
    {
        candidate.clear();

        for(std::uint32_t i{0U}; i < 2U; ++i)
        {
            const std::uint32_t idx{letter_dist(rng())};
            candidate.push_back(letters[static_cast<std::size_t>(idx)]);
        }

        for(std::uint32_t i{0U}; i < 3U; ++i)
        {
            const std::uint32_t idx{digit_dist(rng())};
            candidate.push_back(digits[static_cast<std::size_t>(idx)]);
        }

    } while(assigned_names().find(candidate) != assigned_names().end());

    return candidate;
}

}  // namespace robot_name
