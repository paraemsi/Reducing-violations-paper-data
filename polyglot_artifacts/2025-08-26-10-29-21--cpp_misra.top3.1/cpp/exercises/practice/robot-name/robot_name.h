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

    // Returns the robot's name, generating a new one if needed
    std::string name(void);

    // Resets the robot to factory settings (wipes the name)
    void reset(void);

    // Delete copy and move to avoid duplicate names
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
    robot(robot&&) = delete;
    robot& operator=(robot&&) = delete;

private:
    std::string m_name;
    void generate_name(void);
    static std::unordered_set<std::string> s_used_names;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
