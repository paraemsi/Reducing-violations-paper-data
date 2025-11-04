#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot {
public:
    robot();
    robot(const robot&) = default;
    robot(robot&&) = default;
    auto operator=(const robot&) -> robot& = default;
    auto operator=(robot&&) -> robot& = default;
    ~robot() = default;

    auto name() const -> std::string;
    void reset();

private:
    static auto generate_unique_name() -> std::string;

    std::string m_name;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
