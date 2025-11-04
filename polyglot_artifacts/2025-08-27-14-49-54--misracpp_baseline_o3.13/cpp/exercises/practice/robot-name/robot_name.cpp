#include "robot_name.h"
#include <random>
#include <unordered_set>
#include <mutex>
#include <string>

// Anonymous namespace for implementation details shared across this translation unit
namespace {

std::unordered_set<std::string> used_names;
std::mutex used_names_mutex;

char random_uppercase_letter(std::mt19937& gen) {
    static std::uniform_int_distribution<int> dist('A', 'Z');
    return static_cast<char>(dist(gen));
}

char random_digit(std::mt19937& gen) {
    static std::uniform_int_distribution<int> dist(0, 9);
    return static_cast<char>('0' + dist(gen));
}

std::string generate_random_name(std::mt19937& gen) {
    std::string n;
    n.reserve(5);
    n.push_back(random_uppercase_letter(gen));
    n.push_back(random_uppercase_letter(gen));
    n.push_back(random_digit(gen));
    n.push_back(random_digit(gen));
    n.push_back(random_digit(gen));
    return n;
}

std::string make_unique_name() {
    // Each thread gets its own PRNG, seeded once with hardware entropy
    static thread_local std::mt19937 gen{std::random_device{}()};

    std::lock_guard<std::mutex> lock(used_names_mutex);
    std::string candidate;
    do {
        candidate = generate_random_name(gen);
    } while (used_names.find(candidate) != used_names.end());
    used_names.insert(candidate);
    return candidate;
}

void release_name(const std::string& name) {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    used_names.erase(name);
}

} // unnamed namespace

namespace robot_name {

std::string Robot::generate_unique_name() {
    return make_unique_name();
}

Robot::Robot() : name_(generate_unique_name()) {}

Robot::~Robot() {
    ::release_name(name_);
}

const std::string& Robot::name() const {
    return name_;
}

void Robot::reset() {
    ::release_name(name_);
    name_ = generate_unique_name();
}

}  // namespace robot_name
