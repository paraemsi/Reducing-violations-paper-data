#include "robot_name.h"

#include <sstream>

namespace robot_name {

// Static member definitions
std::unordered_set<std::string> Robot::used_names_{};
std::mt19937 Robot::rng_{std::random_device{}()};
std::mutex Robot::mutex_{};

// Helper to generate a unique name
std::string Robot::generate_unique_name() {
    std::lock_guard<std::mutex> guard(mutex_);
    std::uniform_int_distribution<int> letter_dist('A', 'Z');
    std::uniform_int_distribution<int> digit_dist(0, 9);

    std::string candidate;
    do {
        std::ostringstream oss;
        oss << static_cast<char>(letter_dist(rng_))
            << static_cast<char>(letter_dist(rng_))
            << digit_dist(rng_)
            << digit_dist(rng_)
            << digit_dist(rng_);
        candidate = oss.str();
    } while (used_names_.find(candidate) != used_names_.end());

    used_names_.insert(candidate);
    return candidate;
}

const std::string& Robot::name() const {
    if (m_name.empty()) {
        m_name = generate_unique_name();
    }
    return m_name;
}

void Robot::reset() {
    std::lock_guard<std::mutex> guard(mutex_);
    if (!m_name.empty()) {
        used_names_.erase(m_name);
        m_name.clear();
    }
}

}  // namespace robot_name
