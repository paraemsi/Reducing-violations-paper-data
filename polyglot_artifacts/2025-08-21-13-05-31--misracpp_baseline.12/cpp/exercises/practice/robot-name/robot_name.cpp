#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <mutex>

namespace robot_name {

namespace {
    std::unordered_set<std::string> used_names;
    std::mutex used_names_mutex;

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
    std::string candidate;
    do {
        candidate = random_name();
    } while (is_name_taken(candidate));
    m_name = candidate;
    register_name(m_name);
}

bool Robot::is_name_taken(const std::string& name) {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    return used_names.find(name) != used_names.end();
}

void Robot::register_name(const std::string& name) {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    used_names.insert(name);
}

void Robot::unregister_name(const std::string& name) {
    std::lock_guard<std::mutex> lock(used_names_mutex);
    used_names.erase(name);
}

}  // namespace robot_name
