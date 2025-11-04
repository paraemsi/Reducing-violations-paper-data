#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace kindergarten_garden {

typedef std::uint8_t student_index_t;

enum class Plants
{
    clover,
    grass,
    radishes,
    violets
}; // MISRA C++: semicolon after enum class

class kindergarten_garden
{
public:
    explicit kindergarten_garden(const std::string& diagram);

    std::vector<Plants> plants(const std::string& student) const;

    // Static interface for test compatibility
    static std::vector<Plants> plants(const std::string& diagram, const std::string& student);

private:
    std::vector<std::string> m_rows;
    static const std::vector<std::string> students;
    static student_index_t get_student_index(const std::string& student);
    static Plants char_to_plant(char c);
}; // MISRA C++: semicolon after class

}  // namespace kindergarten_garden
