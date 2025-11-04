#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class Robot
{
public:
    Robot();
    ~Robot() = default;

    Robot(const Robot&) = delete;
    Robot& operator=(const Robot&) = delete;

    Robot(Robot&&) = default;
    Robot& operator=(Robot&&) = default;

    std::string name() const;
    void reset();

private:
    std::string m_name;
    void assign_name();
    static bool is_name_used(const std::string& name);
    static void register_name(const std::string& name);
    static void unregister_name(const std::string& name);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
