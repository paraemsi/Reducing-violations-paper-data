#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class Robot
{
public:
    Robot();
    ~Robot();

    const std::string& name() const;

    void reset();

private:
    std::string m_name;
    static std::string generate_unique_name();
};

// Alias required by tests (lower-case `robot`)
using robot = Robot;  // NOLINT(readability-identifier-naming)

}  // namespace robot_name

#endif // ROBOT_NAME_H
