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

    // Returns the robot's name, generating a new one if needed
    [[nodiscard]] std::string name();

    // Resets the robot to factory settings (wipes the name)
    void reset();

private:
    std::string m_name;

    static std::unordered_set<std::string>& used_names();
    static std::string generate_unique_name();
    static std::string generate_name_candidate();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
