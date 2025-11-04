#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot {
public:
    robot();
    ~robot();
    const std::string& name() const;
    void reset();
private:
    std::string robot_name;
    void generate_name();
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
