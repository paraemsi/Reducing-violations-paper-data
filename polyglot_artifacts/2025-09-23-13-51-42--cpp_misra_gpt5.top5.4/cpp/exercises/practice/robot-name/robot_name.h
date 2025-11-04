#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot final {
public:
    robot();
    ~robot() noexcept;
    robot(const robot&) = delete;
    robot(robot&&) noexcept = default;
    robot& operator=(const robot&) = delete;
    robot& operator=(robot&&) noexcept = default;

    const std::string& name() const;

    void reset() noexcept;

private:
    static std::string generate_unique_name();

    mutable std::string name_{};
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
