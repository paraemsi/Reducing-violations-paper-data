#pragma once

#include <string>
#include <array>
#include <unordered_map>
#include <vector>

namespace kindergarten_garden {

enum class plant { grass, clover, radishes, violets };
enum class Plants { grass, clover, radishes, violets };

std::vector<std::string> default_students();
std::array<Plants, 4> plants(const std::string& diagram, const std::string& student);

class garden {
public:
  explicit garden(const std::string& diagram);
  garden(const std::string& diagram, std::vector<std::string> students);
  std::vector<plant> plants(const std::string& student) const;

private:
  std::unordered_map<std::string, std::vector<plant>> assignments_;
};

}  // namespace kindergarten_garden
