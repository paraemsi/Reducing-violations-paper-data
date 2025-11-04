#include "robot_name.h"
#include <random>
#include <sstream>

namespace robot_name {

using namespace std;

unordered_set<string> Robot::used_names{};
mutex Robot::mutex_;

static thread_local random_device rd;
static thread_local mt19937 gen(rd());
static thread_local uniform_int_distribution<int> letter_dist('A', 'Z');
static thread_local uniform_int_distribution<int> digit_dist(0, 9);

string Robot::generate_unique_name() {
    string candidate;
    lock_guard<mutex> lock(Robot::mutex_);
    do {
        stringstream ss;
        ss << static_cast<char>(letter_dist(gen))
           << static_cast<char>(letter_dist(gen))
           << digit_dist(gen) << digit_dist(gen) << digit_dist(gen);
        candidate = ss.str();
    } while (Robot::used_names.find(candidate) != Robot::used_names.end());

    Robot::used_names.insert(candidate);
    return candidate;
}

Robot::Robot() : _name(generate_unique_name()) {}

const string& Robot::name() const {
    return _name;
}

void Robot::reset() {
    const string old_name = _name;
    {
        lock_guard<mutex> lock(Robot::mutex_);
        Robot::used_names.erase(old_name);
    }
    do {
        _name = generate_unique_name();
    } while (_name == old_name);
}

}  // namespace robot_name
