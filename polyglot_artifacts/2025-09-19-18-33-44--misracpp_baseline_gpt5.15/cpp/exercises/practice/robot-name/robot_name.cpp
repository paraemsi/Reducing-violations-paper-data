#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {
namespace {

// Thread-safe singletons for state shared across all robots.
std::mt19937& prng()
{
    static std::mt19937 rng{std::random_device{}()};
    return rng;
}

char random_letter()
{
    static std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(prng()));
}

char random_digit()
{
    static std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(prng()));
}

std::string random_name()
{
    std::string s;
    s.reserve(5);
    s.push_back(random_letter());
    s.push_back(random_letter());
    s.push_back(random_digit());
    s.push_back(random_digit());
    s.push_back(random_digit());
    return s;
}

std::unordered_set<std::string>& used_names()
{
    static std::unordered_set<std::string> names;
    return names;
}

std::mutex& used_mutex()
{
    static std::mutex m;
    return m;
}

std::string allocate_unique_name()
{
    for (;;) {
        auto candidate = random_name();
        std::lock_guard<std::mutex> lock(used_mutex());
        auto [it, inserted] = used_names().insert(candidate);
        if (inserted) {
            return candidate;
        }
        // else collision; try again
    }
}

void release_name(const std::string& n)
{
    if (n.empty()) return;
    std::lock_guard<std::mutex> lock(used_mutex());
    used_names().erase(n);
}

}  // namespace

robot::robot() = default;

robot::~robot()
{
    release_name(name_);
}





const std::string& robot::name() const
{
    if (name_.empty()) {
        name_ = allocate_unique_name();
    }
    return name_;
}

void robot::reset()
{
    release_name(name_);
    name_.clear();
}

}  // namespace robot_name
