#include "robot_name.h"

#include <array>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>
#include <utility>

namespace robot_name {

namespace {

// Alphabet and digits as lookup tables to avoid any character arithmetic.
constexpr std::array<char, 26U> letters{
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

constexpr std::array<char, 10U> digits{
    '0','1','2','3','4','5','6','7','8','9'
};

// Thread-safe storage for all names that have been issued so far.
std::unordered_set<std::string> used_names{};
std::mutex used_names_mutex{};

// Lazily initialised random number generator (Mersenne Twister 32-bit).
std::mt19937& rng()
{
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

} // anonymous namespace

Robot::Robot() = default;

const std::string& Robot::name() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset()
{
    // Obtain the current name while holding the per-robot mutex,
    // then clear it so that a subsequent call to name() generates
    // a fresh one.  We release the mutex before touching the global
    // name store to avoid any potential dead-lock.
    std::string old_name{};
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        old_name = std::move(m_name);
        m_name.clear();
    }

    if (!old_name.empty()) {
        std::lock_guard<std::mutex> global_lock(used_names_mutex);
        (void)used_names.erase(old_name);
    }
}

std::string Robot::generate_unique_name()
{
    std::string candidate{};
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    for (;;) {
        candidate.clear();

        for (std::uint32_t i = 0U; i < 2U; ++i) {
            const std::uint32_t index = letter_dist(rng());
            candidate.push_back(letters[index]);
        }
        for (std::uint32_t i = 0U; i < 3U; ++i) {
            const std::uint32_t index = digit_dist(rng());
            candidate.push_back(digits[index]);
        }

        // Ensure uniqueness across all robots.
        {
            std::lock_guard<std::mutex> lock(used_names_mutex);
            if (used_names.insert(candidate).second) {
                return candidate;
            }
        }
        // Name collision: loop and try again.
    }
}

}  // namespace robot_name
