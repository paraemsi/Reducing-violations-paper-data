#include "robot_name.h"

#include <array>
#include <cstddef>
#include <iomanip>
#include <sstream>

namespace robot_name {

/* ----------  static member definitions  ---------- */
std::unordered_set<std::string> Robot::s_usedNames {};
std::mt19937                      Robot::s_rng { static_cast<std::mt19937::result_type>(std::random_device {}()) };
std::mutex                        Robot::s_mutex {};

/* ----------  helper: unique name generation  ---------- */
std::string Robot::generate_unique_name()
{
    /* constexpr lookup tables avoid arithmetic on characters                       */
    constexpr std::array<char, 26U> letters { {
        'A','B','C','D','E','F','G','H','I','J','K','L','M',
        'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
    } };

    constexpr std::array<char, 10U> digits  { {
        '0','1','2','3','4','5','6','7','8','9'
    } };

    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U,  9U);

    for (;;) { /* repeat until an unused name is created */
        std::string candidate {};
        candidate.reserve(5U);

        candidate += letters.at(static_cast<std::size_t>(letter_dist(s_rng)));
        candidate += letters.at(static_cast<std::size_t>(letter_dist(s_rng)));
        candidate += digits.at(static_cast<std::size_t>(digit_dist(s_rng)));
        candidate += digits.at(static_cast<std::size_t>(digit_dist(s_rng)));
        candidate += digits.at(static_cast<std::size_t>(digit_dist(s_rng)));

        /* critical section: check / insert unique name */
        {
            std::lock_guard<std::mutex> lock(s_mutex);

            const auto inserted { s_usedNames.insert(candidate) };
            if (inserted.second) {
                return candidate;        /* unique – done */
            }
        }
        /* collision: loop and try again */
    }
}

/* ----------  public interface  ---------- */
Robot::Robot() : m_name {}
{
    /* constructor body intentionally empty */
}

const std::string& Robot::name()
{
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset()
{
    if (!m_name.empty()) {
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            static_cast<void>(s_usedNames.erase(m_name)); /* release old name */
        }
        m_name.clear();
    }
}

}  // namespace robot_name
