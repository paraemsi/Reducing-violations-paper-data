#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

class robot final {
public:
    robot();                              // construct with a unique random name
    ~robot();                             // release the currently-held name

    robot(const robot&)            = delete;
    robot(robot&&)                 = delete;
    robot& operator=(const robot&) = delete;
    robot& operator=(robot&&)      = delete;

    const std::string& name() const;      // return current robot name (never empty)
    void reset();                         // reset to factory settings (new unique name)

private:
    std::string m_name;                   // cached robot name
    static std::string generate_unique_name();   // helper – obtain a unique name
};

}  // namespace robot_name

#endif // ROBOT_NAME_H
