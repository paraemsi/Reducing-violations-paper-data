#include "robot_name.h"

#include <array>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace {

// Allowed characters for name generation (no arithmetic on characters).
static constexpr std::array<char, 26U> kLetters = {
    'A','B','C','D','E','F','G','H','I','J','K','L','M',
    'N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
};

static constexpr std::array<char, 10U> kDigits = {
    '0','1','2','3','4','5','6','7','8','9'
};

// Global registry of assigned names to ensure uniqueness.
static std::unordered_set<std::string>& used_names() {
    static std::unordered_set<std::string> set;
    return set;
}

// Mutex to protect access to the global registry.
static std::mutex& used_names_mutex() {
    static std::mutex mtx;
    return mtx;
}

// Thread-local PRNG seeded with a non-deterministic source.
static std::mt19937& prng() {
    thread_local std::mt19937 engine{std::random_device{}()};
    return engine;
}

// Distributions for indices into the character tables.
static std::uniform_int_distribution<std::size_t>& letter_index_dist() {
    static std::uniform_int_distribution<std::size_t> dist(0U, 25U);
    return dist;
}

static std::uniform_int_distribution<std::size_t>& digit_index_dist() {
    static std::uniform_int_distribution<std::size_t> dist(0U, 9U);
    return dist;
}

}  // namespace

namespace robot_name {

robot::robot()
    : m_name() {
    m_name = generate_unique_name();
}

const std::string& robot::name() const {
    return m_name;
}

void robot::reset() {
    if ((m_name.empty()) == false) {
        std::lock_guard<std::mutex> lock(used_names_mutex());
        (void)used_names().erase(m_name);
    }
    m_name = generate_unique_name();
}

std::string robot::generate_unique_name() {
    for (;;) {
        std::string candidate;
        candidate.reserve(5U);

        // Two letters
        for (std::size_t i = 0U; (i < 2U); ++i) {
            const std::size_t idx = letter_index_dist()(prng());
            candidate.push_back(kLetters.at(idx));
        }

        // Three digits
        for (std::size_t i = 0U; (i < 3U); ++i) {
            const std::size_t idx = digit_index_dist()(prng());
            candidate.push_back(kDigits.at(idx));
        }

        {
            std::lock_guard<std::mutex> lock(used_names_mutex());
            const auto insert_result = used_names().insert(candidate);
            if (insert_result.second) {
                return candidate;
            }
        }
    }
}

}  // namespace robot_name
