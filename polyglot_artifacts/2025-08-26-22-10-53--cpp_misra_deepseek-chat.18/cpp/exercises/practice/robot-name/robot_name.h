#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <set>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();
    std::string name() const;
    void reset();
    
private:
    mutable std::string robot_name;
    mutable bool name_generated;
    static std::string generate_name();
    static std::set<std::string> used_names;
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
