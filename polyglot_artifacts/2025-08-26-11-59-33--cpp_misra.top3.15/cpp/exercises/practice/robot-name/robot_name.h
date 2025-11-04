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

    // Returns the robot's name, generating it if needed
    std::string name(void);

    // Resets the robot to factory settings (wipes name)
    void reset(void);

private:
    std::string m_name;
    static std::unordered_set<std::string> s_used_names;
    static std::string generate_unique_name(void);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
