#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot
{
public:
    robot();
    ~robot();

    robot(const robot&) = delete;
    auto operator=(const robot&) -> robot& = delete;

    robot(robot&&) noexcept;
    auto operator=(robot&&) noexcept -> robot&;

    [[nodiscard]] auto name() const -> const std::string&;

    void reset();

private:
    std::string m_name;

    static auto generate_unique_name() -> std::string;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
