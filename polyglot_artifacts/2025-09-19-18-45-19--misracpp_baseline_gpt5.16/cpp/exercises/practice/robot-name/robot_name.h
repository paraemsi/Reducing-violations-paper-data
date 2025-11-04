#ifndef ROBOT_NAME_H
#define ROBOT_NAME_H

#include <string>

namespace robot_name {

class robot {
public:
  robot();
  std::string name() const;
  void reset();
  ~robot();

  robot(const robot&) = delete;
  robot& operator=(const robot&) = delete;
  robot(robot&&) = delete;
  robot& operator=(robot&&) = delete;

private:
  std::string name_;
};

}  // namespace robot_name

#endif  // ROBOT_NAME_H
