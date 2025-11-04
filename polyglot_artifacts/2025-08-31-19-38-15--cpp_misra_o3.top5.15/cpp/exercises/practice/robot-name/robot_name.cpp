#include "robot_name.h"

#include <array>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

/*----------------------------------------------------------------------------*/
/* Anonymous (internal-linkage) helpers                                       */
/*----------------------------------------------------------------------------*/
namespace
{

/* Alphabet and digit lookup tables – avoid numeric ↔ character conversions */
static constexpr std::array<char, 26U> LETTERS {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};
static constexpr std::array<char, 10U> DIGITS {
    '0','1','2','3','4','5','6','7','8','9'
};

/* Global pool of names currently in use */
static std::unordered_set<std::string>     used_names {};
static std::mutex                          used_names_mutex {};

/* Obtain a shared PRNG instance – thread-safe lazy init */
auto prng() -> std::mt19937&
{
    static std::random_device                               rd {};
    static std::mt19937                                     engine { rd() };
    return engine;
}

/* Generate an unused, random name adhering to the required pattern */
auto generate_random_candidate() -> std::string
{
    std::uniform_int_distribution<std::uint32_t> letter_dist { 0U, 25U };
    std::uniform_int_distribution<std::uint32_t> digit_dist  { 0U, 9U  };

    std::string candidate {};
    candidate.reserve(5U);

    candidate.push_back(LETTERS.at(letter_dist(prng())));
    candidate.push_back(LETTERS.at(letter_dist(prng())));
    candidate.push_back(DIGITS.at(digit_dist(prng())));
    candidate.push_back(DIGITS.at(digit_dist(prng())));
    candidate.push_back(DIGITS.at(digit_dist(prng())));

    return candidate;
}

}   /* anonymous namespace */
/*----------------------------------------------------------------------------*/
/* Robot implementation                                                       */
/*----------------------------------------------------------------------------*/
auto Robot::generate_unique_name() -> std::string
{
    for (;;)   /* loop until a unique name is produced */
    {
        std::string candidate { generate_random_candidate() };

        std::lock_guard<std::mutex> lock { used_names_mutex };
        if (used_names.find(candidate) == used_names.cend())
        {
            /* name is free – reserve and return */
            (void)used_names.insert(candidate);
            return candidate;
        }
    }
}

auto Robot::name() const -> const std::string&
{
    if (m_name.empty())
    {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset()
{
    if (!m_name.empty())
    {
        {
            std::lock_guard<std::mutex> lock { used_names_mutex };
            (void)used_names.erase(m_name);
        }
        m_name.clear();
    }
}

Robot::~Robot() noexcept
{
    if (!m_name.empty())
    {
        std::lock_guard<std::mutex> lock { used_names_mutex };
        (void)used_names.erase(m_name);
    }
}

}  // namespace robot_name
