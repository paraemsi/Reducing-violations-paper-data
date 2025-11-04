#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    std::string name() const;
    void reset();

private:
    std::string robot_name_;
    void generate_name();
    static bool is_name_unique(const std::string& name);
    static void register_name(const std::string& name);
    static void unregister_name(const std::string& name);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
