#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    ~robot() = default;

    robot(const robot&) = delete;
    robot(robot&&) noexcept = default;
    robot& operator=(const robot&) = delete;
    robot& operator=(robot&&) noexcept = default;

    std::string name() const;
    void reset();

private:
    static std::string generate_unique_name();
    static std::string generate_random_name();

    std::string name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
