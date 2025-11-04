#include "robot_name.h"

#include <random>
#include <string>
#include <unordered_set>
#include <mutex>
#include <stdexcept>
#include <cstddef>

namespace {

// Allowed character sets (no arithmetic on character values)
const std::string kLetters("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
const std::string kDigits("0123456789");

// PRNG seeded with non-deterministic source
std::random_device g_rd;
std::mt19937 g_rng(g_rd());

// Distributions producing indices into the above strings
std::uniform_int_distribution<std::size_t> g_letter_dist(
    static_cast<std::size_t>(0U),
    (kLetters.size() - static_cast<std::size_t>(1U)));

std::uniform_int_distribution<std::size_t> g_digit_dist(
    static_cast<std::size_t>(0U),
    (kDigits.size() - static_cast<std::size_t>(1U)));

// Global registry of assigned names with a mutex for thread safety
std::unordered_set<std::string> g_used_names;
std::mutex g_used_names_mutex;

std::size_t capacity() {
    const std::size_t letters_count = kLetters.size();
    const std::size_t digits_count = kDigits.size();
    return (letters_count * letters_count * digits_count * digits_count * digits_count);
}

}  // unnamed namespace

namespace robot_name {

robot::robot() : name_()
{
    name_ = generate_unique_name();
}

const std::string& robot::name() const
{
    return name_;
}

void robot::reset()
{
    release_name(name_);
    name_.clear();
    name_ = generate_unique_name();
}

std::string robot::generate_unique_name()
{
    std::string candidate;
    candidate.reserve(static_cast<std::size_t>(5U));

    for (;;)
    {
        candidate.clear();
        candidate.push_back(kLetters[g_letter_dist(g_rng)]);
        candidate.push_back(kLetters[g_letter_dist(g_rng)]);
        candidate.push_back(kDigits[g_digit_dist(g_rng)]);
        candidate.push_back(kDigits[g_digit_dist(g_rng)]);
        candidate.push_back(kDigits[g_digit_dist(g_rng)]);

        {
            std::lock_guard<std::mutex> lock(g_used_names_mutex);
            if ((g_used_names.size() >= capacity()))
            {
                throw std::runtime_error("No available robot names remain");
            }

            const auto insert_result = g_used_names.insert(candidate);
            if (insert_result.second)
            {
                return candidate;
            }
        }
        // Collision: loop and try again
    }
}

void robot::release_name(const std::string& old_name)
{
    (void)old_name;
    // Do not release names back into the pool.
    // This guarantees that a previously used name is never re-assigned,
    // satisfying tests that expect all generated names to be unique over time.
}

}  // namespace robot_name
