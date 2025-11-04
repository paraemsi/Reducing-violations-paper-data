#include "robot_name.h"
#include <array>
#include <stdexcept>
#include <cstdint>

namespace robot_name {

std::unordered_set<std::string> Robot::s_used_names{};
std::random_device rd{};
std::mt19937 Robot::s_rng{rd()};
std::mutex Robot::s_mutex{};

Robot::Robot() : m_name(generate_unique_name())
{
}

const std::string& Robot::name() const
{
    return m_name;
}

void Robot::reset()
{
    /* Generate a fresh unique name; previously assigned names remain
       reserved to guarantee global uniqueness across the program run. */
    m_name = generate_unique_name();
}

std::string Robot::generate_unique_name()
{
    std::lock_guard<std::mutex> lock(s_mutex);

    std::string candidate{};

    do
    {
        candidate = generate_name_candidate();
    }
    while (s_used_names.find(candidate) != s_used_names.end());

    const auto inserted = s_used_names.insert(candidate);
    if (!inserted.second)
    {
        throw std::runtime_error("Failed to insert unique robot name");
    }

    return candidate;
}

std::string Robot::generate_name_candidate()
{
    static const std::array<char, 26U> letters{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    static const std::array<char, 10U> digits{
        '0','1','2','3','4','5','6','7','8','9'};

    std::string result(5U, '\0');

    {
        std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
        std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

        result[0] = letters[letter_dist(s_rng)];
        result[1] = letters[letter_dist(s_rng)];
        result[2] = digits[digit_dist(s_rng)];
        result[3] = digits[digit_dist(s_rng)];
        result[4] = digits[digit_dist(s_rng)];
    }

    return result;
}

}  // namespace robot_name
