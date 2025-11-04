#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace kindergarten_garden {

enum class plant : std::uint8_t {
  clover,
  grass,
  radishes,
  violets
};

enum class Plants : std::uint8_t {
  clover,
  grass,
  radishes,
  violets
};

class garden {
public:
  explicit garden(const std::string& diagram);

  std::vector<plant> plants(const std::string& student) const;

private:
  std::array<std::string, 2U> rows_{};
  static const std::array<std::string, 12U> default_students_;

  static std::size_t student_index(const std::string& student);
  static plant char_to_plant(const char c);
};

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student);

}  // namespace kindergarten_garden
