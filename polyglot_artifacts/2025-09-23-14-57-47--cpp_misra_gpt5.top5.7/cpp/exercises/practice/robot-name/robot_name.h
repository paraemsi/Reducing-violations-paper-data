#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot() noexcept;
    ~robot() noexcept;

    const std::string& name() const;
    void reset();

    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;
    robot(robot&&) noexcept = default;
    robot& operator=(robot&&) noexcept = default;

private:
    mutable std::string m_name;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
