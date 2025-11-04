#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <map>
#include <algorithm>
#include <iostream>

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
    for (int i = 0; i < children.size(); i++) {
        if (children[i] == student) {
            index = i;
            break;
        }
    }
    
    // Split the diagram into two rows
    size_t newline_pos = diagram.find('\n');
    string row1 = diagram.substr(0, newline_pos);
    string row2 = diagram.substr(newline_pos + 1);
    
    // Ensure both rows have the same length
    // Each child has 2 plants per row, so total plants per row is 2 * number of children
    // Since there are 12 children, each row should have 24 characters
    // But to be safe, we'll use the actual lengths
    
    // Get the plants for the child at the calculated index
    vector<Plants> result;
    
    // First row plants
    int pos = 2 * index;
    char c1 = row1[pos];
    char c2 = row1[pos + 1];
    
    // Second row plants
    char c3 = row2[pos];
    char c4 = row2[pos + 1];
    
    // Helper function to convert char to Plants
    auto charToPlant = [](char c) -> Plants {
        switch (c) {
            case 'C': return Plants::clover;
            case 'G': return Plants::grass;
            case 'R': return Plants::radishes;
            case 'V': return Plants::violets;
            default: throw runtime_error("Invalid plant code");
        }
    };
    
    result.push_back(charToPlant(c1));
    result.push_back(charToPlant(c2));
    result.push_back(charToPlant(c3));
    result.push_back(charToPlant(c4));
    
    return result;
}

}  // namespace kindergarten_garden
