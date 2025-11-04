#include "robot_name.h"

#include <array>
#include <cstddef>
#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {

// Allowed characters
constexpr char LETTERS[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
constexpr char DIGITS[] = "0123456789";

// Global registry of allocated names to ensure uniqueness across all existing robots
std::unordered_set<std::string>& used_names()
{
    static std::unordered_set<std::string> names{};
    return names;
}

std::mutex& used_names_mutex()
{
    static std::mutex m{};
    return m;
}

// Thread-local random engine seeded from std::random_device
std::mt19937& rng()
{
    thread_local std::mt19937 engine{std::random_device{}()};
    return engine;
}

std::string random_name()
{
    auto& eng = rng();

    // Distributions for indices into character tables
    std::uniform_int_distribution<std::uint32_t> letter_dist(0U, 25U);
    std::uniform_int_distribution<std::uint32_t> digit_dist(0U, 9U);

    std::array<char, 5U> buf{};

    // Two letters
    {
        const std::uint32_t li0 = letter_dist(eng);
        const std::size_t idx0 = static_cast<std::size_t>(li0);
        buf[0] = LETTERS[idx0];
    }
    {
        const std::uint32_t li1 = letter_dist(eng);
        const std::size_t idx1 = static_cast<std::size_t>(li1);
        buf[1] = LETTERS[idx1];
    }

    // Three digits
    {
        const std::uint32_t di0 = digit_dist(eng);
        const std::size_t idx0 = static_cast<std::size_t>(di0);
        buf[2] = DIGITS[idx0];
    }
    {
        const std::uint32_t di1 = digit_dist(eng);
        const std::size_t idx1 = static_cast<std::size_t>(di1);
        buf[3] = DIGITS[idx1];
    }
    {
        const std::uint32_t di2 = digit_dist(eng);
        const std::size_t idx2 = static_cast<std::size_t>(di2);
        buf[4] = DIGITS[idx2];
    }

    return std::string(buf.data(), buf.size());
}

std::string allocate_unique_name()
{
    for (;;) {
        const std::string candidate = random_name();

        {
            std::lock_guard<std::mutex> lock(used_names_mutex());
            const auto it = used_names().find(candidate);
            if ((it == used_names().end())) {
                (void)used_names().insert(candidate);
                return candidate;
            }
        }
        // Collision: loop and try again
    }
}

} // namespace

robot::robot()
    : m_name(allocate_unique_name())
{
}

std::string robot::name() const
{
    return m_name;
}

void robot::reset()
{
    {
        std::lock_guard<std::mutex> lock(used_names_mutex());
        if ((!m_name.empty())) {
            (void)used_names().erase(m_name);
        }
    }

    m_name = allocate_unique_name();
}

}  // namespace robot_name
