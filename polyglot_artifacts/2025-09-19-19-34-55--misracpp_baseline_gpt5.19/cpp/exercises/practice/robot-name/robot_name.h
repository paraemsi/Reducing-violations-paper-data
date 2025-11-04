#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();

    // Returns the robot's name. Generates one on first call if not set.
    const std::string& name() const;
    void reset();

    // Non-copyable; movable with ownership transfer to preserve global uniqueness constraints.
    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
    robot(robot&&) noexcept;
    robot& operator=(robot&&) noexcept;

private:
    mutable std::string name_;
    static std::string generate_unique_name();
    static void release_name(const std::string& name);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
