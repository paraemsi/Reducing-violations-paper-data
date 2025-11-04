#ifndef ROBOT_NAME_H
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>

namespace robot_name {

class Robot {
public:
    Robot();
    ~Robot();
    const std::string& name() const; // first call generates a name
    void reset();              // wipe current name so next call to name() generates a new one

private:
    std::string _name;

    // helpers
    void generate_unique_name();
    static std::string generate_random_name();

    // global registry of names already taken
    static std::unordered_set<std::string> s_used_names;
};

// Alias with lowercase name expected by the tests
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
