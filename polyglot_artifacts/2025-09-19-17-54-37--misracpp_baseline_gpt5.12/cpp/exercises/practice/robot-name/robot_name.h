#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();

    // Non-copyable to maintain uniqueness guarantees across live robots
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;

    // Movable to support use in standard containers
    robot(robot&& other) noexcept;
    robot& operator=(robot&& other) noexcept;

    std::string name() const;
    void reset();

private:
    std::string name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
