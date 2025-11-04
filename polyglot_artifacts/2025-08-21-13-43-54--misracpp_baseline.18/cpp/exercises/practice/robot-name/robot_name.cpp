#include "robot_name.h"
#include <random>
#include <set>
#include <mutex>
#include <string>
#include <cctype>
#include <sstream>
#include <iomanip>

namespace robot_name {

namespace {
    // Set of all assigned robot names
    std::set<std::string> assigned_names;
    std::mutex assigned_names_mutex;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> letter_dist('A', 'Z');
    std::uniform_int_distribution<> digit_dist(0, 9);

    std::string random_name() {
        std::string name;
        name += static_cast<char>(letter_dist(gen));
        name += static_cast<char>(letter_dist(gen));
        for (int i = 0; i < 3; ++i) {
            name += static_cast<char>('0' + digit_dist(gen));
        }
        return name;
    }

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

Robot::~Robot() {
    if (!m_name.empty()) {
        unregister_name(m_name);
    }
}

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
    std::string candidate;
    do {
        candidate = random_name();
    } while (is_name_taken(candidate));
    m_name = candidate;
    register_name(m_name);
}

}  // namespace robot_name
