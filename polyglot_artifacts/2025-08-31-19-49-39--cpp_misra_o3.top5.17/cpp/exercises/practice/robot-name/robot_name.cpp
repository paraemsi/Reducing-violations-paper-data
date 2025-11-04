#include "robot_name.h"

#include <array>
#include <unordered_set>
#include <random>
#include <cstdint>

namespace robot_name {

namespace {

// Internal storage for all allocated robot names (ensures uniqueness).
std::unordered_set<std::string> &used_names()
{
    static std::unordered_set<std::string> s_used_names{};
    return s_used_names;
}

// Single shared random-number engine.
std::mt19937 &rng_engine()
{
    static std::random_device rd{};
    static std::mt19937 engine{rd()};
    return engine;
}

} // unnamed namespace

robot::robot() : m_name{}
{
    m_name = generate_unique_name();
}

std::string const & robot::name()
{
    if(m_name.empty())
    {
        m_name = generate_unique_name();
    }

    return m_name;
}

std::string const & robot::name() const
{
    return m_name;
}

void robot::reset()
{
    if(!m_name.empty())
    {
        (void)used_names().erase(m_name);
        m_name.clear();
    }
}

std::string robot::generate_unique_name()
{
    static constexpr std::array<char, 26U> letters{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    };
    static constexpr std::array<char, 10U> digits{
        '0','1','2','3','4','5','6','7','8','9'
    };

    std::uniform_int_distribution<std::size_t> letter_dist{0U, letters.size() - 1U};
    std::uniform_int_distribution<std::size_t> digit_dist{0U, digits.size() - 1U};

    std::string candidate{};

    do
    {
        candidate.clear();

        for(std::uint32_t i{0U}; i < 2U; ++i)
        {
            candidate.push_back(letters.at(letter_dist(rng_engine())));
        }
        for(std::uint32_t i{0U}; i < 3U; ++i)
        {
            candidate.push_back(digits.at(digit_dist(rng_engine())));
        }
    } while(used_names().find(candidate) != used_names().end());

    (void)used_names().insert(candidate);

    return candidate;
}

}  // namespace robot_name
