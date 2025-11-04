#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <array>
using namespace std;

namespace kindergarten_garden {

array<Plants, 4> plants(const string& diagram, const string& student) {
    // Split the diagram into two rows
    stringstream ss(diagram);
    string row1, row2;
    getline(ss, row1);
    getline(ss, row2);
    
    // List of children in order
    vector<string> children = {
        "Alice", "Bob", "Charlie", "David", 
        "Eve", "Fred", "Ginny", "Harriet", 
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = find(children.begin(), children.end(), student);
    int index = distance(children.begin(), it);
    
    // Calculate start position for the child's plants
    int start = 2 * index;
    
    // Get plants from both rows
    char c1 = row1[start];
    char c2 = row1[start + 1];
    char c3 = row2[start];
    char c4 = row2[start + 1];
    
    // Convert each character to Plants enum
    auto convert = [](char c) -> Plants {
        switch(c) {
            case 'G': return Plants::grass;
            case 'C': return Plants::clover;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: return Plants::grass; // Should not happen according to the instructions
        }
    };
    
    return {
        convert(c1),
        convert(c2),
        convert(c3),
        convert(c4)
    };
}

}  // namespace kindergarten_garden
