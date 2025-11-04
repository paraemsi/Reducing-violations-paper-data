#include "robot_name.h"

#include <array>
#include <cstddef>
#include <unordered_set>
#include <random>
#include <mutex>

namespace robot_name {

namespace {

// Container that stores every name in use
static std::unordered_set<std::string> g_used_names {};
// Mutex protects the shared set – tests may be multithreaded
static std::mutex g_mutex {};

// Character pools – no arithmetic on character values
constexpr std::array<char, 26U> letters {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

constexpr std::array<char, 10U> digits {
    '0','1','2','3','4','5','6','7','8','9'
};

// PRNG – seeded once
std::string random_name()
{
    // Generators are heavy, build them once
    static std::random_device rd {};
    static std::mt19937 generator { rd() };

    /* use explicit casts to satisfy MISRA – avoid implicit narrowing from
       std::size_t (returned by size()) to std::uint32_t expected by the
       distribution’s template parameter */
    std::uniform_int_distribution<std::uint32_t> letter_dist{
        static_cast<std::uint32_t>(0),
        static_cast<std::uint32_t>(letters.size() - static_cast<std::size_t>(1U))
    };
    /* same explicit-cast rationale as above */
    std::uniform_int_distribution<std::uint32_t> digit_dist{
        static_cast<std::uint32_t>(0),
        static_cast<std::uint32_t>(digits.size() - static_cast<std::size_t>(1U))
    };

    std::string result {};
    result.reserve(5U);

    result.push_back(letters[letter_dist(generator)]);
    result.push_back(letters[letter_dist(generator)]);

    result.push_back(digits[digit_dist(generator)]);
    result.push_back(digits[digit_dist(generator)]);
    result.push_back(digits[digit_dist(generator)]);

    return result;
}

} // unnamed namespace

// static
std::string robot::generate_unique_name()
{
    for(;;) {
        const std::string candidate { random_name() };

        // Protect against data races when multiple robots are created/reset
        std::lock_guard<std::mutex> lock { g_mutex };

        const auto inserted = g_used_names.insert(candidate);
        if(inserted.second) {
            return candidate;   // unique – done
        }
    }
}

robot::robot() : m_name(generate_unique_name())
{
    // ctor body intentionally left empty
}

const std::string& robot::name() const noexcept
{
    return m_name;
}

void robot::reset()
{
    // Release current name
    {
        std::lock_guard<std::mutex> lock { g_mutex };
        (void)g_used_names.erase(m_name);
    }
    m_name = generate_unique_name();
}

}  // namespace robot_name
