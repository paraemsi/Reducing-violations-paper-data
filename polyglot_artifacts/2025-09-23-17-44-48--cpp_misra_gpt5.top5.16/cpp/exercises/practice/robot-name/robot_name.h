#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot final {
public:
    robot() noexcept;
    robot(const robot&) = delete;
    robot(robot&&) = delete;
    auto operator=(const robot&) -> robot& = delete;
    auto operator=(robot&&) -> robot& = delete;
    ~robot() noexcept;

    auto name() const -> const std::string&;
    void reset();

private:
    mutable std::string m_name;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
