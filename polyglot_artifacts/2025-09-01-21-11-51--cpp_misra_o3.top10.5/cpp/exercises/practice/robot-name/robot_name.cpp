#include "robot_name.h"

namespace {

// Letter and digit lookup tables avoid any numeric ↔ character conversions
constexpr std::array<char, 26U> LETTERS
{
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

constexpr std::array<char, 10U> DIGITS
{
    '0','1','2','3','4','5','6','7','8','9'
};

} // unnamed namespace

namespace robot_name {

std::unordered_set<std::string> Robot::s_used_names {};

std::mt19937& Robot::prng()
{
    static std::random_device rd {};
    static std::mt19937 rng (rd());
    return rng;
}

std::string Robot::generate_unique_name()
{
    auto& rng = prng();
    std::uniform_int_distribution<std::size_t> letter_dist (0U, LETTERS.size() - 1U);
    std::uniform_int_distribution<std::size_t> digit_dist (0U, DIGITS.size() - 1U);

    std::string candidate {};

    do
    {
        candidate.clear();
        candidate.push_back(LETTERS[letter_dist(rng)]);
        candidate.push_back(LETTERS[letter_dist(rng)]);
        candidate.push_back(DIGITS[digit_dist(rng)]);
        candidate.push_back(DIGITS[digit_dist(rng)]);
        candidate.push_back(DIGITS[digit_dist(rng)]);
    }
    while (s_used_names.find(candidate) != s_used_names.end());

    (void)s_used_names.insert(candidate);

    return candidate;
}

Robot::Robot() :
    m_name(generate_unique_name())
{
}

/* defaulted destructor – no cleanup necessary, names remain reserved */

const std::string& Robot::name() const noexcept
{
    return m_name;
}

void Robot::reset()
{
    s_used_names.erase(m_name);
    m_name = generate_unique_name();
}

}  // namespace robot_name
