#include "kindergarten_garden.h"
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

namespace kindergarten_garden {

    vector<Plants> plants(const string& diagram, const string& child) {
        // Split the diagram into two lines
        size_t newline_pos = diagram.find('\n');
        if (newline_pos == string::npos) {
            return {};
        }
        
        string row1 = diagram.substr(0, newline_pos);
        string row2 = diagram.substr(newline_pos + 1);
        
        // Trim any carriage return characters (for Windows compatibility)
        if (!row2.empty() && row2.back() == '\r') {
            row2.pop_back();
        }
        
        // List of children in order
        vector<string> children = {
            "Alice", "Bob", "Charlie", "David",
            "Eve", "Fred", "Ginny", "Harriet",
            "Ileana", "Joseph", "Kincaid", "Larry"
        };
        
        // Find the index of the child
        int index = -1;
        for (int i = 0; i < children.size(); i++) {
            if (children[i] == child) {
                index = i;
                break;
            }
        }
        
        if (index == -1) {
            return {};
        }
        
        // Get the plant codes for this child
        int start = 2 * index;
        vector<Plants> result;
        
        // Helper function to convert char to Plants
        auto charToPlant = [](char c) -> Plants {
            switch (c) {
                case 'G': return grass;
                case 'C': return clover;
                case 'R': return radishes;
                case 'V': return violets;
                default: return grass; // Should not happen according to the problem
            }
        };
        
        // Add plants from first row
        result.push_back(charToPlant(row1[start]));
        result.push_back(charToPlant(row1[start + 1]));
        // Add plants from second row
        result.push_back(charToPlant(row2[start]));
        result.push_back(charToPlant(row2[start + 1]));
        
        return result;
    }

}  // namespace kindergarten_garden
