#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <sstream>

using namespace std;

namespace kindergarten_garden {

vector<Plants> plants(const string& diagram, const string& child) {
    // Split the diagram into two rows
    size_t newline_pos = diagram.find('\n');
    string first_row = diagram.substr(0, newline_pos);
    string second_row = diagram.substr(newline_pos + 1);
    
    // List of children in order
    const vector<string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the child
    auto it = find(children.begin(), children.end(), child);
    int index = distance(children.begin(), it);
    
    // Get the starting index for the child's plants in each row
    int start = 2 * index;
    
    // Convert characters to Plants enum
    vector<Plants> result;
    
    // Helper lambda to convert char to enum
    auto char_to_plant = [](char c) {
        switch (c) {
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::clover;
        }
    };
    
    // Add plants from first row
    result.push_back(char_to_plant(first_row[start]));
    result.push_back(char_to_plant(first_row[start + 1]));
    // Add plants from second row
    result.push_back(char_to_plant(second_row[start]));
    result.push_back(char_to_plant(second_row[start + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
