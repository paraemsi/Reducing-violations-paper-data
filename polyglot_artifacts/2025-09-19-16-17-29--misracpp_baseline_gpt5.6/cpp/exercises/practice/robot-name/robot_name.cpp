#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>
#include <utility>

namespace robot_name {

namespace {

// Set of all names currently allocated to any existing robot.
std::unordered_set<std::string> used_names;

// Guard access to used_names and name assignment to ensure thread safety.
std::mutex used_mutex;

// Single PRNG instance seeded with non-deterministic random_device once.
std::mt19937& rng()
{
    static std::mt19937 gen{std::random_device{}()};
    return gen;
}

std::string make_random_name()
{
    static std::uniform_int_distribution<int> letter_dist('A', 'Z');
    static std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string s;
    s.reserve(5);
    s.push_back(static_cast<char>(letter_dist(rng())));
    s.push_back(static_cast<char>(letter_dist(rng())));
    s.push_back(static_cast<char>('0' + digit_dist(rng())));
    s.push_back(static_cast<char>('0' + digit_dist(rng())));
    s.push_back(static_cast<char>('0' + digit_dist(rng())));
    return s;
}

}  // namespace

const std::string& robot::name() const
{
    if (!name_.empty()) {
        return name_;
    }

    std::lock_guard<std::mutex> lk(used_mutex);

    // Double-check after acquiring the lock to avoid races on first initialization.
    if (name_.empty()) {
        std::string candidate;
        do {
            candidate = make_random_name();
        } while (used_names.find(candidate) != used_names.end());

        used_names.insert(candidate);
        name_ = candidate;
    }

    return name_;
}

robot::robot(const robot& other)
{
    std::lock_guard<std::mutex> lk(used_mutex);
    if (!other.name_.empty()) {
        std::string candidate;
        do {
            candidate = make_random_name();
        } while (used_names.find(candidate) != used_names.end());
        used_names.insert(candidate);
        name_ = std::move(candidate);
    }
}

robot& robot::operator=(const robot& other)
{
    if (this != &other) {
        std::lock_guard<std::mutex> lk(used_mutex);
        if (!name_.empty()) {
            // Do not release the name back to the pool to avoid reusing names.
            name_.clear();
        }
        if (!other.name_.empty()) {
            std::string candidate;
            do {
                candidate = make_random_name();
            } while (used_names.find(candidate) != used_names.end());
            used_names.insert(candidate);
            name_ = std::move(candidate);
        }
    }
    return *this;
}

void robot::reset()
{
    std::lock_guard<std::mutex> lk(used_mutex);
    // Do not release the name back to the pool to avoid reusing names.
    if (!name_.empty()) {
        name_.clear();
    }
}

}  // namespace robot_name
