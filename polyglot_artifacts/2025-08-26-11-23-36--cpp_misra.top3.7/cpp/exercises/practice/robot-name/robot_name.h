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
    [[nodiscard]] std::string name(void);

    // Resets the robot to factory settings (wipes name)
    void reset(void);

private:
    std::string m_name;
    static std::unordered_set<std::string> s_used_names;

    // Generates a unique random name
    static std::string generate_unique_name(void);

    // Helper to generate a random name candidate
    static std::string generate_name_candidate(void);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
