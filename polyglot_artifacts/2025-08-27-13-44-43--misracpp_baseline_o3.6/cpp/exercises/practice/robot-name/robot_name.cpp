#include "robot_name.h"

#include <random>
#include <unordered_set>
#include <mutex>

namespace {

// shared state for all robots
std::unordered_set<std::string> used_names;
std::mutex names_mutex;

// random engine helpers
std::mt19937& rng()
{
    static std::mt19937 engine{ std::random_device{}() };
    return engine;
}

char random_upper_letter()
{
    std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(rng()));
}

char random_digit()
{
    std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(rng()));
}

std::string generate_name()
{
    std::string n;
    n.reserve(5);
    n.push_back(random_upper_letter());
    n.push_back(random_upper_letter());
    n.push_back(random_digit());
    n.push_back(random_digit());
    n.push_back(random_digit());
    return n;
}

} // namespace

namespace robot_name {

robot::robot() : name_{ generate_unique_name() } {}

const std::string& robot::name() const
{
    return name_;
}

void robot::reset()
{
    // Generate a new unique name first. This call internally acquires
    // the mutex, so we *must not* hold the lock while calling it.
    std::string new_name = generate_unique_name();

    // Now replace our current name and release the old one while holding the lock.
    std::lock_guard<std::mutex> lock(names_mutex);
    used_names.erase(name_);
    name_ = std::move(new_name);
}

std::string robot::generate_unique_name()
{
    std::lock_guard<std::mutex> lock(names_mutex);
    std::string candidate;
    do {
        candidate = generate_name();
    } while (used_names.find(candidate) != used_names.end());

    used_names.insert(candidate);
    return candidate;
}

}  // namespace robot_name
