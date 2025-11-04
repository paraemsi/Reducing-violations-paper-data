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

    // Returns the robot's name, generating one if needed
    std::string name(void);

    // Resets the robot to factory settings (wipes name)
    void reset();

private:
    std::string m_name;
    static std::unordered_set<std::string> s_used_names;

    // Generates a unique random name
    static std::string generate_unique_name(void);

    // Generates a random name in the correct format
    static std::string generate_name(void);

    // Helper for random number generation
    static std::uint32_t random_uint32(std::uint32_t min, std::uint32_t max);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
