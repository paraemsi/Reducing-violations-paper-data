#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
using namespace std;

namespace kindergarten_garden {

vector<Plants> plants(const string& diagram, const string& student) {
    // List of children in order
    const vector<string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    int index = -1;
    for (size_t i = 0; i < children.size(); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two rows
    size_t newline_pos = diagram.find('\n');
    string row1 = diagram.substr(0, newline_pos);
    string row2 = diagram.substr(newline_pos + 1);
    
    // Each child gets two plants from each row
    int start_pos = index * 2;
    vector<Plants> result;
    
    // Convert characters to Plants enum
    auto to_plant = [](char c) {
        switch (c) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::grass;
        }
    };
    
    result.push_back(to_plant(row1[start_pos]));
    result.push_back(to_plant(row1[start_pos + 1]));
    result.push_back(to_plant(row2[start_pos]));
    result.push_back(to_plant(row2[start_pos + 1]));
    
    return result;
}

}  // namespace kindergarten_garden
