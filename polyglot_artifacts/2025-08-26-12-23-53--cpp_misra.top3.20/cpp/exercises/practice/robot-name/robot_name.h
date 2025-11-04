#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>
#include <unordered_set>
#include <memory>

namespace robot_name {

class robot
{
public:
    robot();
    ~robot();

    // Returns the robot's name, generating a new one if needed
    std::string name(void);

    // Resets the robot to factory settings (wipes the name)
    void reset();

private:
    std::string m_name {};
    void generate_name(void);

    // Disallow copy and assignment
    robot(robot const&) = delete;
    robot& operator=(robot const&) = delete;

    // Static set to track all assigned names
    static std::unordered_set<std::string>& assigned_names(void);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
