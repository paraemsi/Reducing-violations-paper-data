#include "robot_name.h"

#include <array>
#include <cstddef>
#include <random>

namespace robot_name {

// Static member definitions.
std::unordered_set<std::string> Robot::s_used_names{};
std::mutex Robot::s_mutex{};

namespace {

// Character tables – no arithmetic on char values (MISRA compliant).
constexpr std::array<char, 26U> LETTERS{{
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
}};

constexpr std::array<char, 10U> DIGITS{{'0','1','2','3','4','5','6','7','8','9'}};

// Random-engine accessor – local static to avoid static-initialisation order fiasco.
std::mt19937& rng()
{
    static std::mt19937 engine{std::random_device{}()};
    return engine;
}

} // unnamed namespace

Robot::Robot() : m_name{generate_unique_name()}
{
}

std::string Robot::name() const noexcept
{
    return m_name;
}

void Robot::reset()
{
    // Acquire a new unique name and swap it in.
    m_name = generate_unique_name();
}

std::string Robot::generate_unique_name()
{
    std::uniform_int_distribution<std::uint32_t> letter_dist{0U, 25U};
    std::uniform_int_distribution<std::uint32_t> digit_dist{0U, 9U};

    std::string candidate{};
    candidate.reserve(5U);

    while (true) {
        candidate.clear();
        // Two letters.
        candidate.push_back(LETTERS[static_cast<std::size_t>(letter_dist(rng()))]);
        candidate.push_back(LETTERS[static_cast<std::size_t>(letter_dist(rng()))]);
        // Three digits.
        candidate.push_back(DIGITS[static_cast<std::size_t>(digit_dist(rng()))]);
        candidate.push_back(DIGITS[static_cast<std::size_t>(digit_dist(rng()))]);
        candidate.push_back(DIGITS[static_cast<std::size_t>(digit_dist(rng()))]);

        // Ensure uniqueness under lock.
        {
            std::lock_guard<std::mutex> lock{s_mutex};
            const auto [it, inserted] = s_used_names.insert(candidate);
            static_cast<void>(it); // value unused, MISRA: cast to void
            if (inserted) {
                return candidate;
            }
        }
        // Collision – loop to try again.
    }
}

}  // namespace robot_name
