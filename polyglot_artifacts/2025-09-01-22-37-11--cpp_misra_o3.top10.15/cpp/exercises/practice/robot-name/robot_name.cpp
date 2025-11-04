#include "robot_name.h"
#include <string>
#include <unordered_set>
#include <random>
#include <cstdint>
#include <cstddef>
#include <array>

namespace robot_name {

namespace
{
    // Generate a raw random name in the format LLDDD (e.g., "RX837").
    std::string generate_name()
    {
        static std::random_device rd;
        static std::mt19937 engine{ rd() };
        static std::uniform_int_distribution<std::uint32_t> dist_letter(0U, 25U);
        static std::uniform_int_distribution<std::uint32_t> dist_digit(0U, 9U);

        constexpr std::array<char, 26U> letters{
            'A','B','C','D','E','F','G','H','I','J','K','L','M',
            'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
        };

        std::string result{};
        result.reserve(5U);

        result.push_back(letters[static_cast<std::size_t>(dist_letter(engine))]);
        result.push_back(letters[static_cast<std::size_t>(dist_letter(engine))]);

        constexpr std::array<char, 10U> digits{
            '0','1','2','3','4','5','6','7','8','9'
        };

        result.push_back(digits[static_cast<std::size_t>(dist_digit(engine))]);
        result.push_back(digits[static_cast<std::size_t>(dist_digit(engine))]);
        result.push_back(digits[static_cast<std::size_t>(dist_digit(engine))]);

        return result;
    }

    // Ensure global uniqueness of robot names.
    std::string generate_unique_name_internal()
    {
        static std::unordered_set<std::string> used_names{};

        std::string candidate{ generate_name() };

        while ((used_names.find(candidate) != used_names.end()))
        {
            candidate = generate_name();
        }

        used_names.insert(candidate);
        return candidate;
    }
} // anonymous namespace

robot::robot() : name_{ generate_unique_name() }
{
}

const std::string& robot::name() const noexcept
{
    return name_;
}

void robot::reset()
{
    // Assign a fresh unique name.
    name_ = generate_unique_name();
}

std::string robot::generate_unique_name()
{
    return generate_unique_name_internal();
}

}  // namespace robot_name
