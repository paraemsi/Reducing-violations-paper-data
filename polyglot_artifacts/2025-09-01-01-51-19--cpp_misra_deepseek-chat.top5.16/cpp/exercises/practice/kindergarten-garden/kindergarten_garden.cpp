#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <array>
#include <sstream>
#include <cstdint>

namespace kindergarten_garden {

std::vector<Plants> plants(const std::string& diagram, const std::string& student) {
    // List of children in order
    const std::array<std::string, 12> children = {
        "Alice", "Bob", "Charlie", "David", "Eve", "Fred",
        "Ginny", "Harriet", "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    std::int32_t index = 0;
    for (std::int32_t i = 0; i < 12; i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two lines
    std::istringstream iss(diagram);
    std::string line1;
    std::string line2;
    std::getline(iss, line1);
    std::getline(iss, line2);
    
    // Each child has 2 plants per row, so their plants are at index*2 to index*2+1
    std::vector<Plants> result;
    
    // Get the starting position for the child's plants
    const std::int32_t start_pos = index * 2;
    
    // Process first line
    {
        const char first_plant = line1[start_pos];
        if (first_plant == 'G') {
            result.push_back(Plants::grass);
        } else { 
            if (first_plant == 'C') {
                result.push_back(Plants::clover);
            } else { 
                if (first_plant == 'R') {
                    result.push_back(Plants::radishes);
                } else { 
                    if (first_plant == 'V') {
                        result.push_back(Plants::violets);
                    }
                }
            }
        }
    }
    {
        const char second_plant = line1[start_pos + 1];
        if (second_plant == 'G') {
            result.push_back(Plants::grass);
        } else { 
            if (second_plant == 'C') {
                result.push_back(Plants::clover);
            } else { 
                if (second_plant == 'R') {
                    result.push_back(Plants::radishes);
                } else { 
                    if (second_plant == 'V') {
                        result.push_back(Plants::violets);
                    }
                }
            }
        }
    }
    
    // Process second line
    {
        const char first_plant = line2[start_pos];
        if (first_plant == 'G') {
            result.push_back(Plants::grass);
        } else { 
            if (first_plant == 'C') {
                result.push_back(Plants::clover);
            } else { 
                if (first_plant == 'R') {
                    result.push_back(Plants::radishes);
                } else { 
                    if (first_plant == 'V') {
                        result.push_back(Plants::violets);
                    }
                }
            }
        }
    }
    {
        const char second_plant = line2[start_pos + 1];
        if (second_plant == 'G') {
            result.push_back(Plants::grass);
        } else { 
            if (second_plant == 'C') {
                result.push_back(Plants::clover);
            } else { 
                if (second_plant == 'R') {
                    result.push_back(Plants::radishes);
                } else { 
                    if (second_plant == 'V') {
                        result.push_back(Plants::violets);
                    }
                }
            }
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
