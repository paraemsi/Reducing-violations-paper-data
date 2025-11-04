#include "kindergarten_garden.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>

namespace kindergarten_garden {

std::vector<std::string> default_students() {
  return {"Alice",  "Bob",   "Charlie", "David",  "Eve",    "Fred",
          "Ginny",  "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"};
}

namespace {
plant plant_from_char(char c) {
  switch (c) {
    case 'G':
      return plant::grass;
    case 'C':
      return plant::clover;
    case 'R':
      return plant::radishes;
    case 'V':
      return plant::violets;
    default:
      throw std::invalid_argument("Unknown plant code");
  }
}
Plants plants_from_char(char c) {
  switch (c) {
    case 'G':
      return Plants::grass;
    case 'C':
      return Plants::clover;
    case 'R':
      return Plants::radishes;
    case 'V':
      return Plants::violets;
    default:
      throw std::invalid_argument("Unknown plant code");
  }
}
}  // namespace

garden::garden(const std::string& diagram) : garden(diagram, default_students()) {}

garden::garden(const std::string& diagram, std::vector<std::string> students) {
  // Split diagram into two rows
  const auto nl = diagram.find('\n');
  if (nl == std::string::npos) {
    throw std::invalid_argument("Diagram must contain exactly two rows");
  }
  const std::string row1 = diagram.substr(0, nl);
  const auto nl2 = diagram.find('\n', nl + 1);
  const std::string row2 =
      diagram.substr(nl + 1, (nl2 == std::string::npos) ? std::string::npos : nl2 - (nl + 1));

  // Sort students alphabetically
  std::sort(students.begin(), students.end());

  // Validate basic structure
  const std::size_t cups_per_row = row1.size();
  if (row2.size() != cups_per_row) {
    throw std::invalid_argument("Diagram must contain exactly two rows of equal length");
  }
  if (cups_per_row % 2 != 0) {
    throw std::invalid_argument("Each row must have an even number of cups");
  }
  const std::size_t expected_students = cups_per_row / 2;
  if (students.size() != expected_students) {
    throw std::invalid_argument("Number of students must match diagram width / 2");
  }

  for (std::size_t i = 0; i < students.size(); ++i) {
    std::vector<plant> ps;
    ps.reserve(4);
    ps.push_back(plant_from_char(row1[2 * i]));
    ps.push_back(plant_from_char(row1[2 * i + 1]));
    ps.push_back(plant_from_char(row2[2 * i]));
    ps.push_back(plant_from_char(row2[2 * i + 1]));
    assignments_.emplace(students[i], std::move(ps));
  }
}

std::vector<plant> garden::plants(const std::string& student) const {
  const auto it = assignments_.find(student);
  if (it == assignments_.end()) {
    return {};
  }
  return it->second;
}

std::array<Plants, 4> plants(const std::string& diagram, const std::string& student) {
  // Split diagram into two rows
  const auto nl = diagram.find('\n');
  if (nl == std::string::npos) {
    throw std::invalid_argument("Diagram must contain exactly two rows");
  }
  const std::string row1 = diagram.substr(0, nl);
  const auto nl2 = diagram.find('\n', nl + 1);
  const std::string row2 =
      diagram.substr(nl + 1, (nl2 == std::string::npos) ? std::string::npos : nl2 - (nl + 1));

  if (row1.size() != row2.size()) {
    throw std::invalid_argument("Diagram must contain exactly two rows of equal length");
  }
  if (row1.size() % 2 != 0) {
    throw std::invalid_argument("Each row must have an even number of cups");
  }

  const std::size_t num_students = row1.size() / 2;

  auto students = default_students();
  if (num_students > students.size()) {
    throw std::invalid_argument("Diagram width exceeds number of known students");
  }
  // students are already alphabetical in default_students
  students.resize(num_students);

  const auto it = std::find(students.begin(), students.end(), student);
  if (it == students.end()) {
    throw std::invalid_argument("Student not found in this diagram");
  }
  const std::size_t idx = static_cast<std::size_t>(std::distance(students.begin(), it));

  std::array<Plants, 4> result{
      plants_from_char(row1[2 * idx]),
      plants_from_char(row1[2 * idx + 1]),
      plants_from_char(row2[2 * idx]),
      plants_from_char(row2[2 * idx + 1]),
  };
  return result;
}

}  // namespace kindergarten_garden
