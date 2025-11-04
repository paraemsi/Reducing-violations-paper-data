#include "robot_name.h"

#include <array>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace
{
    /*  global (translation-unit) storage for all names in use
        guarded by a mutex to ensure thread-safety                                           */
    std::unordered_set<std::string> used_names{};
    std::mutex used_names_mutex{};
}  // unnamed namespace

namespace robot_name {

Robot::Robot() : name_() {}

Robot::~Robot() noexcept
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    if (!name_.empty())
    {
        (void)used_names.erase(name_);
    }
}

const std::string& Robot::name() const
{
    /*  Single-lock implementation to avoid the data-race caused
        by reading and writing `name_` outside the critical section. */
    std::lock_guard<std::mutex> lock(used_names_mutex);

    if (name_.empty())
    {
        std::string candidate{};
        do
        {
            candidate = generate_name();
        }
        while (used_names.find(candidate) != used_names.end());

        (void)used_names.insert(candidate);
        name_ = candidate;
    }

    return name_;
}

void Robot::reset()
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    if (!name_.empty())
    {
        (void)used_names.erase(name_);
    }
    name_.clear();
}

std::string Robot::generate_name()
{
    static const std::array<char, 26U> letters = {
        'A','B','C','D','E','F','G','H','I','J',
        'K','L','M','N','O','P','Q','R','S','T',
        'U','V','W','X','Y','Z'
    };

    static const std::array<char, 10U> digits = {
        '0','1','2','3','4','5','6','7','8','9'
    };

    static std::random_device rd;
    static std::mt19937 engine(rd());
    static std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    static std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::string candidate{};
    candidate.reserve(5U);

    candidate.push_back(letters[letter_dist(engine)]);
    candidate.push_back(letters[letter_dist(engine)]);
    candidate.push_back(digits[digit_dist(engine)]);
    candidate.push_back(digits[digit_dist(engine)]);
    candidate.push_back(digits[digit_dist(engine)]);

    return candidate;
}

}  // namespace robot_name
