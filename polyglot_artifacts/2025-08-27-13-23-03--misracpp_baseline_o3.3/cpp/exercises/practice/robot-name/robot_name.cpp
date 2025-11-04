#include "robot_name.h"

#include <random>
#include <mutex>
#include <sstream>
#include <iomanip>
#include <unordered_set>
#include <utility>   // for std::move et al. (future-proofing, no behavioral change)

namespace robot_name {

std::unordered_set<std::string> Robot::used_names{};

std::mt19937& Robot::rng() {
    static std::mt19937 engine(std::random_device{}());
    return engine;
}

std::mutex& Robot::mutex() {
    static std::mutex mtx;
    return mtx;
}

std::string Robot::generate_unique_name() {
    std::uniform_int_distribution<int> letter_dist(0, 25);
    std::uniform_int_distribution<int> digit_dist(0, 999);

    auto& gen = rng();
    std::lock_guard<std::mutex> lock(mutex());

    std::string candidate;
    do {
        candidate.clear();
        candidate.push_back(static_cast<char>('A' + letter_dist(gen)));
        candidate.push_back(static_cast<char>('A' + letter_dist(gen)));

        int digits = digit_dist(gen);
        std::ostringstream oss;
        oss << std::setw(3) << std::setfill('0') << digits;
        candidate += oss.str();
    } while (!used_names.insert(candidate).second); // repeat until unique

    return candidate;
}

Robot::Robot() : _name(generate_unique_name()) {}

Robot::~Robot() {
    std::lock_guard<std::mutex> lock(mutex());
    used_names.erase(_name);
}

const std::string& Robot::name() const noexcept {
    return _name;
}

void Robot::reset() {
    {
        std::lock_guard<std::mutex> lock(mutex());
        used_names.erase(_name);
    }
    _name = generate_unique_name();
}

}  // namespace robot_name
