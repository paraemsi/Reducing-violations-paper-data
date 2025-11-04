#include "robot_name.h"

#include <random>

namespace robot_name {

std::unordered_set<std::string> Robot::s_used_names{};
std::mutex Robot::s_names_mutex{};

Robot::Robot() : _name(generate_name())
{
}

Robot::~Robot()
{
    std::lock_guard<std::mutex> lock(s_names_mutex);
    (void)s_used_names.erase(_name);
}

const std::string& Robot::name() const noexcept
{
    return _name;
}

void Robot::reset()
{
    {
        std::lock_guard<std::mutex> lock(s_names_mutex);
        (void)s_used_names.erase(_name);
    }
    _name = generate_name();
}

std::string Robot::generate_name()
{
    static const std::array<char, 26U> letters{
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};

    static const std::array<char, 10U> digits{
        '0','1','2','3','4','5','6','7','8','9'};

    static std::mt19937 engine{[]() {
        std::random_device rd{};
        const auto seed_value{static_cast<std::uint32_t>(rd())};
        return std::mt19937{seed_value};
    }()};

    std::uniform_int_distribution<std::uint32_t> dist_letter(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> dist_digit(0U, 9U);

    for (;;) {
        std::string candidate(5U, '\0');
        for (std::size_t i{0U}; i < 2U; ++i) {
            candidate[i] = letters[dist_letter(engine)];
        }
        for (std::size_t i{2U}; i < 5U; ++i) {
            candidate[i] = digits[dist_digit(engine)];
        }

        std::lock_guard<std::mutex> lock(s_names_mutex);
        const auto result = s_used_names.insert(candidate);
        if (result.second) {
            return candidate;
        }
    }
}

}  // namespace robot_name
