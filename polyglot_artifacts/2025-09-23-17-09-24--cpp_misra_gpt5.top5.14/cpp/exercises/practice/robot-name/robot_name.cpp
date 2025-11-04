#include "robot_name.h"

#include <cstdint>
#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {

// Constants for allowed characters
constexpr std::uint32_t kLettersCount = static_cast<std::uint32_t>(26U);
constexpr std::uint32_t kDigitsCount = static_cast<std::uint32_t>(10U);
const std::string kLetters = std::string("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const std::string kDigits = std::string("0123456789");

// Global registry of allocated names (ensures uniqueness among existing robots)
std::unordered_set<std::string>& allocated_set() {
    static std::unordered_set<std::string> s{};
    return s;
}

std::unordered_set<std::string>& used_set() {
    static std::unordered_set<std::string> u{};
    return u;
}

std::mutex& allocated_mutex() {
    static std::mutex m{};
    return m;
}

// Thread-local PRNG seeded from non-deterministic source
std::mt19937& rng() {
    thread_local static std::mt19937 gen{std::random_device{}()};
    return gen;
}

// Uniform index in [0, upper_exclusive - 1]
std::uint32_t uniform_index(const std::uint32_t upper_exclusive) {
    std::uniform_int_distribution<std::uint32_t> dist(
        static_cast<std::uint32_t>(0U),
        static_cast<std::uint32_t>(upper_exclusive - static_cast<std::uint32_t>(1U))
    );
    return dist(rng());
}

// Generate a unique robot name in the form: LLDDD
std::string generate_unique_name() {
    for (;;) {
        std::string candidate{};
        candidate.reserve(static_cast<std::size_t>(5U));

        candidate.push_back(kLetters.at(static_cast<std::size_t>(uniform_index(kLettersCount))));
        candidate.push_back(kLetters.at(static_cast<std::size_t>(uniform_index(kLettersCount))));
        candidate.push_back(kDigits.at(static_cast<std::size_t>(uniform_index(kDigitsCount))));
        candidate.push_back(kDigits.at(static_cast<std::size_t>(uniform_index(kDigitsCount))));
        candidate.push_back(kDigits.at(static_cast<std::size_t>(uniform_index(kDigitsCount))));

        {
            std::lock_guard<std::mutex> lock(allocated_mutex());
            auto& used = used_set();
            const auto inserted_used = used.insert(candidate);
            if (inserted_used.second) {
                (void)allocated_set().insert(candidate);
                return candidate;
            }
        }
        // Collision occurred; try again.
    }
}

}  // namespace

robot::robot() noexcept = default;

robot::~robot() {
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(allocated_mutex());
        (void)allocated_set().erase(m_name);
    }
}

std::string robot::name() const {
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void robot::reset() {
    if (!m_name.empty()) {
        std::lock_guard<std::mutex> lock(allocated_mutex());
        (void)allocated_set().erase(m_name);
        m_name.clear();
    }
}

}  // namespace robot_name
