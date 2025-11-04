#include "robot_name.h"

#include <random>
#include <string>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {

// Character sets (no arithmetic on characters)
static const std::string kLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const std::string kDigits  = "0123456789";

// Thread-local PRNG seeded from std::random_device
static std::mt19937_64& rng()
{
    thread_local std::mt19937_64 eng = []() {
        std::random_device rd;
        const auto seed_raw = rd();
        const std::mt19937_64::result_type seed =
            static_cast<std::mt19937_64::result_type>(seed_raw);
        return std::mt19937_64(seed);
    }();
    return eng;
}

// Distributions for indices into the character sets
static std::uniform_int_distribution<std::size_t>& letter_dist()
{
    static std::uniform_int_distribution<std::size_t> dist(0U, 25U);
    return dist;
}

static std::uniform_int_distribution<std::size_t>& digit_dist()
{
    static std::uniform_int_distribution<std::size_t> dist(0U, 9U);
    return dist;
}

// Global registry of in-use names with a mutex for thread safety
static std::unordered_set<std::string>& used_names()
{
    static std::unordered_set<std::string> names{};
    return names;
}

static std::mutex& used_names_mutex()
{
    static std::mutex m{};
    return m;
}

// Create a random name candidate (format: LLDDD)
static std::string make_random_name()
{
    std::string s{};
    s.reserve(5U);

    auto& eng = rng();

    s.push_back(kLetters.at(letter_dist()(eng)));
    s.push_back(kLetters.at(letter_dist()(eng)));
    s.push_back(kDigits.at(digit_dist()(eng)));
    s.push_back(kDigits.at(digit_dist()(eng)));
    s.push_back(kDigits.at(digit_dist()(eng)));

    return s;
}

} // anonymous namespace

robot::robot()
    : m_name(generate_unique_name())
{
}

const std::string& robot::name() const
{
    return m_name;
}

void robot::reset()
{
    m_name = generate_unique_name();
}

std::string robot::generate_unique_name()
{
    for (;;)
    {
        const std::string candidate = make_random_name();
        {
            std::lock_guard<std::mutex> lock(used_names_mutex());
            const auto insert_result = used_names().insert(candidate);
            if (insert_result.second)
            {
                return candidate;
            }
        }
    }
}

}  // namespace robot_name
