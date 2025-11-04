#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <cstdint>
#include <mutex>
#include <string>
#include <unordered_set>

namespace robot_name {

class Robot {
public:
    Robot();

    // Return the current robot name (always 2 letters + 3 digits).
    [[nodiscard]] std::string name() const noexcept;

    // Reset the robot to factory settings. A subsequent call to name()
    // will provide a new, **unique** name.
    void reset();

private:
    std::string m_name;                             // NOLINT(cppcoreguidelines-non-private-member-variables-in-classes)

    // Generate a fresh unique robot name.
    static std::string generate_unique_name();

    // Container tracking all names handed out so far.
    static std::unordered_set<std::string> s_used_names;

    // Serialise access to the container above.
    static std::mutex s_mutex;
};

// Provide the lower-case alias expected by the tests.
using robot = Robot;

}  // namespace robot_name

#endif // ROBOT_NAME_H
