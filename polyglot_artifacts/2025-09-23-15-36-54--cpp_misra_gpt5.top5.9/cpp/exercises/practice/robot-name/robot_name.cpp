#include "robot_name.h"

#include <mutex>
#include <random>
#include <stdexcept>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {

// Thread-local PRNG seeded from random_device.
inline std::mt19937& rng()
{
    thread_local std::random_device rd;
    thread_local std::mt19937 eng(rd());
    return eng;
}

// Character pools (no arithmetic on character values).
static const std::string kLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
static const std::string kDigits = "0123456789";

// Global registry of allocated names; protected by a mutex.
std::unordered_set<std::string> used_names;
std::mutex used_names_mtx;

// Maximum number of unique names available: 26 * 26 * 1000.
constexpr std::size_t kMaxNames =
    ((static_cast<std::size_t>(26)) * (static_cast<std::size_t>(26)) * (static_cast<std::size_t>(1000)));

}  // namespace

robot::robot()
    : name_(generate_unique_name())
{
}


std::string robot::name() const
{
    return name_;
}

void robot::reset()
{
    {
        std::lock_guard<std::mutex> lock(used_names_mtx);
        (void)used_names.erase(name_);
    }
    name_ = generate_unique_name();
}

std::string robot::generate_unique_name()
{
    {
        std::lock_guard<std::mutex> lock(used_names_mtx);
        if ((used_names.size()) >= kMaxNames)
        {
            throw std::runtime_error("No more unique robot names available");
        }
    }

    for (;;)
    {
        const std::string candidate = generate_random_name();
        std::lock_guard<std::mutex> lock(used_names_mtx);
        const bool inserted = (used_names.insert(candidate).second);
        if (inserted)
        {
            return candidate;
        }
    }
}

std::string robot::generate_random_name()
{
    std::string out;
    out.reserve(static_cast<std::size_t>(5));

    std::uniform_int_distribution<std::size_t> letter_dist(
        static_cast<std::size_t>(0),
        (kLetters.size() - static_cast<std::size_t>(1)));

    std::uniform_int_distribution<std::size_t> digit_dist(
        static_cast<std::size_t>(0),
        (kDigits.size() - static_cast<std::size_t>(1)));

    std::mt19937& eng = rng();

    out.push_back(kLetters[letter_dist(eng)]);
    out.push_back(kLetters[letter_dist(eng)]);
    out.push_back(kDigits[digit_dist(eng)]);
    out.push_back(kDigits[digit_dist(eng)]);
    out.push_back(kDigits[digit_dist(eng)]);

    return out;
}

}  // namespace robot_name
