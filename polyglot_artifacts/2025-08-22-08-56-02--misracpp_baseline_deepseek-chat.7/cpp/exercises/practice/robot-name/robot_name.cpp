#include "robot_name.h"
#include <random>
#include <string>
#include <unordered_set>
#include <stdexcept>
#include <sstream>
#include <iomanip>
using namespace std;

namespace robot_name {

unordered_set<string> robot::used_names;

string robot::generate_name() {
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> letter_dist(0, 25);
    static uniform_int_distribution<> number_dist(0, 999);
    
    string name;
    while (true) {
        // Generate two random letters
        name.clear();
        name += 'A' + letter_dist(gen);
        name += 'A' + letter_dist(gen);
        
        // Generate a number between 0-999 and format it to three digits
        int number = number_dist(gen);
        stringstream num_ss;
        num_ss << setw(3) << setfill('0') << number;
        name += num_ss.str();
        
        // Check if the name is unique
        if (used_names.find(name) == used_names.end()) {
            used_names.insert(name);
            break;
        }
    }
    return name;
}

robot::robot() : name_(generate_name()) {
}

std::string robot::name() const {
    return name_;
}

void robot::reset() {
    // Remove the current name from used_names
    used_names.erase(name_);
    // Generate a new unique name
    name_ = generate_name();
}

}  // namespace robot_name
