#include "robot_name.h"
#include <unordered_set>
#include <random>
#include <array>
#include <mutex>
#include <cstddef>
#include <utility>

namespace robot_name {

static std::unordered_set<std::string> used_names{};
static std::mutex used_names_mutex{};

namespace
{
static std::string generate_name()
{
    static constexpr std::array<char, 26U> letters{{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    }};
    static constexpr std::array<char, 10U> digits{{
        '0','1','2','3','4','5','6','7','8','9'
    }};

    static std::mt19937 engine{std::random_device{}()};
    static std::uniform_int_distribution<std::uint32_t> letter_dist{0U, 25U};
    static std::uniform_int_distribution<std::uint32_t> digit_dist{0U, 9U};

    std::string result{};
    result.reserve(5U);
    result.push_back(letters[static_cast<std::size_t>(letter_dist(engine))]);
    result.push_back(letters[static_cast<std::size_t>(letter_dist(engine))]);
    result.push_back(digits[static_cast<std::size_t>(digit_dist(engine))]);
    result.push_back(digits[static_cast<std::size_t>(digit_dist(engine))]);
    result.push_back(digits[static_cast<std::size_t>(digit_dist(engine))]);

    return result;
}
} // unnamed namespace

std::string Robot::generate_unique_name()
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    std::string new_name{};
    do
    {
        new_name = generate_name();
    } while (used_names.find(new_name) != used_names.end());

    (void)used_names.insert(new_name);
    return new_name;
}

Robot::Robot() : m_name{generate_unique_name()}
{
}

Robot::~Robot()
{
    // Destructor intentionally does not remove the name from
    // the global set so that names are never reused.
}

Robot::Robot(Robot&& other) noexcept
{
    std::lock_guard<std::mutex> lock(used_names_mutex);
    m_name = std::move(other.m_name);
    other.m_name.clear();
}

Robot& Robot::operator=(Robot&& other) noexcept
{
    if(this != &other)
    {
        std::lock_guard<std::mutex> lock(used_names_mutex);
        m_name = std::move(other.m_name);
        other.m_name.clear();
    }
    return *this;
}

std::string Robot::name() const
{
    return m_name;
}

void Robot::reset()
{
    m_name = generate_unique_name(); // no erase: keep all names unique globally
}

}  // namespace robot_name
