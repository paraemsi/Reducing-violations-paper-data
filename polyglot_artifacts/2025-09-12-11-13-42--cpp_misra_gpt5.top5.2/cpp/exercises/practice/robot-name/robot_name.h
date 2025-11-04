#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot {
public:
    robot();
    robot(robot const&) = default;
    robot(robot&&) noexcept = default;
    robot& operator=(robot const&) = default;
    robot& operator=(robot&&) noexcept = default;
    ~robot() = default;

    const std::string& name() const;
    void reset();

private:
    static std::string generate_unique_name();
    static void release_name(const std::string& old_name);

    std::string name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
