#include "robot_name.h"

#include <random>
#include <unordered_set>
#include <mutex>
#include <string>
#include <cstddef>
#include <cstdint>

namespace
{
    /* Local helpers and data are kept inside an anonymous namespace
       to avoid polluting the public namespace. */

    std::unordered_set<std::string> g_used_names{};
    std::mutex g_mutex{};

    std::string generate_candidate_name()
    {
        static std::random_device rd{};
        static std::mt19937 gen{rd()};
        static std::uniform_int_distribution<std::uint16_t> dist_letter{0U, 25U};
        static std::uniform_int_distribution<std::uint16_t> dist_digit{0U, 9U};

        static const std::string kLetters{"ABCDEFGHIJKLMNOPQRSTUVWXYZ"};
        static const std::string kDigits{"0123456789"};

        std::string candidate{};
        candidate.reserve(5U);

        candidate.push_back(kLetters.at(static_cast<std::size_t>(dist_letter(gen))));
        candidate.push_back(kLetters.at(static_cast<std::size_t>(dist_letter(gen))));

        for (std::uint8_t i{0U}; i < static_cast<std::uint8_t>(3); ++i)
        {
            candidate.push_back(
                kDigits.at(static_cast<std::size_t>(dist_digit(gen))));
        }

        return candidate;
    }
} // anonymous namespace

namespace robot_name {

Robot::Robot()
    : m_name(generate_unique_name())
{
}


[[nodiscard]] const std::string& Robot::name() const noexcept
{
    return m_name;
}

void Robot::reset() noexcept
{
    /* Re-generate a unique name.  
       No need to remove the previous name from the set – keeping it
       reserved guarantees that names are never re-used. */
    m_name = generate_unique_name();
}

std::string Robot::generate_unique_name() noexcept
{
    std::lock_guard<std::mutex> lock(g_mutex);

    std::string candidate{generate_candidate_name()};
    while ((g_used_names.find(candidate) != g_used_names.end()))
    {
        candidate = generate_candidate_name();
    }

    (void)g_used_names.insert(candidate);
    return candidate;
}

}  // namespace robot_name
