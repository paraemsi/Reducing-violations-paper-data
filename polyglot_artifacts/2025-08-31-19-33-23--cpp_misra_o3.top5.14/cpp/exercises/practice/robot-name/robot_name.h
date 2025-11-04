#if !defined(ROBOT_NAME_H)
#define ROBOT_NAME_H

#include <string>
#include <cstdint>

namespace robot_name {

/*
 * Class robot
 * -----------
 * Provides a unique, randomly generated name for each instance,
 * following the pattern: two uppercase letters followed by three digits
 * (e.g. "RX837"). Calling reset() wipes the current name; the next call
 * to name() will provide a new, unique value.
 */
class robot
{
public:
    robot();
    const std::string& name() const;
    void reset() const;

private:
    void generate_name() const;

    mutable std::string current_name_;
};

}  // namespace robot_name

#endif  // ROBOT_NAME_H
