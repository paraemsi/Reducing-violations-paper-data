#include "kindergarten_garden.h"
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <array>
using namespace std;

namespace kindergarten_garden {

array<Plants, 4> plants(string diagram, string student) {
    // List of children in order
    const vector<string> children = {
        "Alice", "Bob", "Charlie", "David",
        "Eve", "Fred", "Ginny", "Harriet",
        "Ileana", "Joseph", "Kincaid", "Larry"
    };
    
    // Find the index of the student
    auto it = find(children.begin(), children.end(), student);
    if (it == children.end()) {
        // Handle error case, though tests should provide valid names
        return array<Plants, 4>();
    }
    int index = distance(children.begin(), it);
    
    // Split the diagram into two rows
    size_t split_pos = diagram.find('\n');
    string row1 = diagram.substr(0, split_pos);
    string row2 = diagram.substr(split_pos + 1);
    
    // Get the plants for the child
    array<Plants, 4> result;
    
    // Process first row
    for (int i = 0; i < 2; i++) {
        char c = row1[2 * index + i];
        switch (c) {
            case 'G': result[i] = Plants::grass; break;
            case 'C': result[i] = Plants::clover; break;
            case 'R': result[i] = Plants::radishes; break;
            case 'V': result[i] = Plants::violets; break;
            default: break;
        }
    }
    
    // Process second row
    for (int i = 0; i < 2; i++) {
        char c = row2[2 * index + i];
        switch (c) {
            case 'G': result[i + 2] = Plants::grass; break;
            case 'C': result[i + 2] = Plants::clover; break;
            case 'R': result[i + 2] = Plants::radishes; break;
            case 'V': result[i + 2] = Plants::violets; break;
            default: break;
        }
    }
    
    return result;
}

}  // namespace kindergarten_garden
