#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
    robot();
    std::string name();
    void reset();

private:
    std::string robot_name_;
    void generate_name();
    static bool is_name_unique(std::string const&);
    static void register_name(std::string const&);
    static void unregister_name(std::string const&);
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
