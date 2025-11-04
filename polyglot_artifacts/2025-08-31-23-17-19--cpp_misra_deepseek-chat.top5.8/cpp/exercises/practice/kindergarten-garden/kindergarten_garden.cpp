#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <array>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::int32_t index = -1;
    for (std::int32_t i = 0; i < 12; i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two rows
    std::size_t split_pos = diagram.find('\n');
    std::string row1 = diagram.substr(0, split_pos);
    std::string row2 = diagram.substr(split_pos + 1);
    
    // Get the positions for the student's plants
    std::int32_t start_pos = 2 * index;
    std::vector<Plants> result;
    
    // Helper function to convert character to Plants enum
    auto char_to_plant = [](char c) -> Plants {
        if (c == 'G') { 
            return Plants::grass; 
        } else { 
            if (c == 'C') { 
                return Plants::clover; 
            } else { 
                if (c == 'R') { 
                    return Plants::radishes; 
                } else { 
                    if (c == 'V') { 
                        return Plants::violets; 
                    } else { 
                        // Handle error case, though according to the problem, this won't happen
                        return Plants::grass;
                    } 
                } 
            } 
        }
    };
    
    // Add plants from first row
    result.push_back(char_to_plant(row1[static_cast<std::size_t>(start_pos)]));
    result.push_back(char_to_plant(row1[static_cast<std::size_t>(start_pos + 1)]));
    // Add plants from second row
    result.push_back(char_to_plant(row2[static_cast<std::size_t>(start_pos)]));
    result.push_back(char_to_plant(row2[static_cast<std::size_t>(start_pos + 1)]));
    
    return result;
}

}  // namespace kindergarten_garden
