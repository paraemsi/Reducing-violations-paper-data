#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <unordered_set>
#include <cstdint>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();

    robot(const robot&) = delete;
    robot& operator=(const robot&) = delete;

    robot(robot&&) noexcept;
    robot& operator=(robot&&) noexcept;

    std::string name() const;
    void reset();

private:
    std::string m_name;
    void assign_name();
    static std::unordered_set<std::string>& used_names();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
