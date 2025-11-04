#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();
    
    // Get the current name of the robot
    std::string name() const;
    
    // Reset the robot to factory settings (generates a new name)
    void reset();

private:
    std::string name_;
    
    // Static set to track all used names across all robots
    static std::unordered_set<std::string> used_names;
    
    // Generate a new unique random name
    std::string generate_unique_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
