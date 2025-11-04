#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();

    robot(const robot&);
    robot& operator=(const robot&);
    robot(robot&&) noexcept;
    robot& operator=(robot&&) noexcept;

    const std::string& name() const;
    void reset();

private:
    static std::string generate_unique_name(const std::string& avoid = {});
    static void release_name(const std::string& name);

    std::string name_;
    std::string last_name_;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
