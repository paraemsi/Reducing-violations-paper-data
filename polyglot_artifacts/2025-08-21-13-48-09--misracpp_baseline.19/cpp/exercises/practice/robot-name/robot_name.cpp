#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {
    // Thread-safe set of assigned names
    std::unordered_set<std::string> assigned_names;
    std::mutex assigned_names_mutex;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist('A', 'Z');
    std::uniform_int_distribution<> digit_dist(0, 9);

    // Helper functions for name management
    bool is_name_taken(const std::string& name) {
        std::lock_guard<std::mutex> lock(assigned_names_mutex);
        return assigned_names.find(name) != assigned_names.end();
    }

    void register_name(const std::string& name) {
        std::lock_guard<std::mutex> lock(assigned_names_mutex);
        assigned_names.insert(name);
    }

    void unregister_name(const std::string& name) {
        std::lock_guard<std::mutex> lock(assigned_names_mutex);
        assigned_names.erase(name);
    }
}

Robot::Robot() : m_name("") {}

std::string Robot::name() {
    if (m_name.empty()) {
        generate_name();
    }
    return m_name;
}

void Robot::reset() {
    if (!m_name.empty()) {
        unregister_name(m_name);
        m_name.clear();
    }
}

void Robot::generate_name() {
    std::string new_name;
    do {
        new_name.clear();
        new_name += static_cast<char>(letter_dist(gen));
        new_name += static_cast<char>(letter_dist(gen));
        for (int i = 0; i < 3; ++i) {
            new_name += static_cast<char>('0' + digit_dist(gen));
        }
    } while (is_name_taken(new_name));
    m_name = new_name;
    register_name(m_name);
}

}  // namespace robot_name
