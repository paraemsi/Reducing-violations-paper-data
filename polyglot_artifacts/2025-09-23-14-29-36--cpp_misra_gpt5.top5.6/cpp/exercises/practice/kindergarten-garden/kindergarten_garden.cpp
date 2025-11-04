#include "kindergarten_garden.h"

#include <stdexcept>

namespace kindergarten_garden {

const std::array<std::string, 12U> garden::default_students_ = {
    "Alice",  "Bob",   "Charlie", "David",
    "Eve",    "Fred",  "Ginny",   "Harriet",
    "Ileana", "Joseph","Kincaid", "Larry"
};

garden::garden(const std::string& diagram) {
  const std::size_t pos = diagram.find('\n');
  if (pos == std::string::npos) {
    throw std::invalid_argument("diagram must contain two rows separated by a newline");
  }

  rows_[0U] = diagram.substr(0U, pos);
  rows_[1U] = diagram.substr((pos + 1U));

  if ((rows_[0U].size() != rows_[1U].size()) || (((rows_[0U].size() % 2U) != 0U))) {
    throw std::invalid_argument("both rows must have equal even length");
  }
}

std::vector<plant> garden::plants(const std::string& student) const {
  const std::size_t idx = student_index(student);
  const std::size_t col0 = (idx * 2U);
  const std::size_t col1 = (col0 + 1U);

  if (((rows_[0U].size() <= col1) || (rows_[1U].size() <= col1))) {
    throw std::out_of_range("student index out of range for garden width");
  }

  std::vector<plant> result{};
  result.reserve(4U);

  result.push_back(char_to_plant(rows_[0U].at(col0)));
  result.push_back(char_to_plant(rows_[0U].at(col1)));
  result.push_back(char_to_plant(rows_[1U].at(col0)));
  result.push_back(char_to_plant(rows_[1U].at(col1)));

  return result;
}

std::size_t garden::student_index(const std::string& student) {
  for (std::size_t i = 0U; i < default_students_.size(); ++i) {
    if (default_students_[i] == student) {
      return i;
    }
  }
  throw std::invalid_argument("unknown student");
}

plant garden::char_to_plant(const char c) {
  if ((c == 'G')) {
    return plant::grass;
  } else if ((c == 'C')) {
    return plant::clover;
  } else if ((c == 'R')) {
    return plant::radishes;
  } else if ((c == 'V')) {
    return plant::violets;
  } else {
    throw std::invalid_argument("invalid plant code");
  }
}

namespace {

inline Plants to_Plants(const plant p) {
  switch (p) {
    case plant::clover:
      return Plants::clover;
    case plant::grass:
      return Plants::grass;
    case plant::radishes:
      return Plants::radishes;
    case plant::violets:
      return Plants::violets;
    default:
      throw std::invalid_argument("invalid plant enum");
  }
}

}  // unnamed namespace

std::array<Plants, 4U> plants(const std::string& diagram, const std::string& student) {
  const garden g(diagram);
  const std::vector<plant> v = g.plants(student);

  if ((v.size() != 4U)) {
    throw std::runtime_error("expected four plants for student");
  }

  std::array<Plants, 4U> out{};
  out[0U] = to_Plants(v.at(0U));
  out[1U] = to_Plants(v.at(1U));
  out[2U] = to_Plants(v.at(2U));
  out[3U] = to_Plants(v.at(3U));
  return out;
}

}  // namespace kindergarten_garden
