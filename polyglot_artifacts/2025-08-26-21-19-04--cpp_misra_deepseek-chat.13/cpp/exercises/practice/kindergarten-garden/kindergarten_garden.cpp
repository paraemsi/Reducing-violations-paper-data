#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::vector<std::string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = std::find(children.begin(), children.end(), student);
    // Since the student must be found, we can assume it exists
    std::int32_t index = static_cast<std::int32_t>(it - children.begin());
    
    // Split the diagram into non-empty lines
    std::istringstream iss(diagram);
    std::vector<std::string> rows;
    std::string line;
    while (std::getline(iss, line)) {
        if (!line.empty()) {
            rows.push_back(line);
        }
    }
    
    // We should have exactly two rows
    if (rows.size() < 2) {
        return {};
    }
    
    const std::string& row1 = rows[0];
    const std::string& row2 = rows[1];
    
    // Each child gets two plants from each row, at positions index*2 and index*2 +1
    std::vector<Plants> result;
    
    // Process first row
    for (std::int32_t i = 0; i < 2; ++i) {
        std::int32_t pos = (index * 2) + i;
        if (pos < static_cast<std::int32_t>(row1.size())) {
            char plantCode = row1[pos];
            switch (plantCode) {
                case 'G': result.emplace_back(Plants::grass); break;
                case 'C': result.emplace_back(Plants::clover); break;
                case 'R': result.emplace_back(Plants::radishes); break;
                case 'V': result.emplace_back(Plants::violets); break;
                default: break;
            }
        }
    }
    
    // Process second row
    for (std::int32_t i = 0; i < 2; ++i) {
        std::int32_t pos = (index * 2) + i;
        if (pos < static_cast<std::int32_t>(row2.size())) {
            char plantCode = row2[pos];
            switch (plantCode) {
                case 'G': result.emplace_back(Plants::grass); break;
                case 'C': result.emplace_back(Plants::clover); break;
                case 'R': result.emplace_back(Plants::radishes); break;
                case 'V': result.emplace_back(Plants::violets); break;
                default: break;
            }
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
