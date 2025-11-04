#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {

// Shared container tracking names that are currently in use.
std::unordered_set<std::string> used_names;
std::mutex names_mutex;

// Produce a random candidate name (may collide with an existing one).
std::string random_name()
{
    static thread_local std::mt19937 gen(std::random_device{}());
    std::uniform_int_distribution<int> letter_dist('A', 'Z');
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string s;
    s.reserve(5);
    s.push_back(static_cast<char>(letter_dist(gen)));
    s.push_back(static_cast<char>(letter_dist(gen)));
    for (int i = 0; i < 3; ++i) {
        s.push_back(static_cast<char>('0' + digit_dist(gen)));
    }
    return s;
}

} // anonymous namespace

bool Robot::is_name_unique(const std::string& candidate)
{
    std::lock_guard<std::mutex> lock(names_mutex);
    return used_names.find(candidate) == used_names.end();
}

void Robot::register_name(const std::string& new_name)
{
    std::lock_guard<std::mutex> lock(names_mutex);
    used_names.insert(new_name);
}

void Robot::unregister_name(const std::string& old_name)
{
    if (old_name.empty()) return;
    std::lock_guard<std::mutex> lock(names_mutex);
    used_names.erase(old_name);
}

std::string Robot::generate_unique_name()
{
    std::lock_guard<std::mutex> lock(names_mutex);

    std::string candidate;
    do {
        candidate = random_name();
    } while (used_names.find(candidate) != used_names.end());

    used_names.insert(candidate);
    return candidate;
}

Robot::Robot()
    : _name(generate_unique_name())
{
}

Robot::~Robot() = default;

const std::string& Robot::name() const
{
    return _name;
}

void Robot::reset()
{
    _name = generate_unique_name();
}

}  // namespace robot_name
