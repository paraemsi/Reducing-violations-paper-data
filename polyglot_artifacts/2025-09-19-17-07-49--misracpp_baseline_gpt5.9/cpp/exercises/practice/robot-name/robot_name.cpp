#include "robot_name.h"

#include <mutex>
#include <random>
#include <string>
#include <unordered_set>

namespace robot_name {

namespace {

// Thread-safe RNG seeded with non-deterministic seed
std::mt19937& rng()
{
    static std::mt19937 gen(std::random_device{}());
    return gen;
}

char random_upper_letter()
{
    static std::uniform_int_distribution<int> dist(0, 25);
    return static_cast<char>('A' + dist(rng()));
}

char random_digit()
{
    static std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(rng()));
}

std::string random_name()
{
    std::string s;
    s.reserve(5);
    s.push_back(random_upper_letter());
    s.push_back(random_upper_letter());
    s.push_back(random_digit());
    s.push_back(random_digit());
    s.push_back(random_digit());
    return s;
}

// Global registry of used names to ensure uniqueness across all robots
std::unordered_set<std::string>& used_names()
{
    static std::unordered_set<std::string> set;
    return set;
}

std::mutex& registry_mutex()
{
    static std::mutex m;
    return m;
}

std::string generate_unique_name()
{
    std::lock_guard<std::mutex> lock(registry_mutex());
    auto& set = used_names();

    std::string candidate;
    do {
        candidate = random_name();
    } while (set.find(candidate) != set.end());

    set.insert(candidate);
    return candidate;
}

}  // namespace

robot::robot()
    : name_(generate_unique_name())
{}

const std::string& robot::name() const
{
    return name_;
}

void robot::reset()
{
    name_ = generate_unique_name();
}

}  // namespace robot_name
