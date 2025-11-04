#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>
#include <unordered_set>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();

    // Returns the robot's name, generating it if needed
    std::string name();

    // Resets the robot to factory settings (wipes name)
    void reset(void);

private:
    std::string m_name;
    static std::unordered_set<std::string> s_used_names;

    // Generates a unique random name
    static std::string generate_unique_name();

    // Generates a random name in the correct format
    static std::string generate_name();

    // Disallow copy and assignment
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
