#include "diamond.h"
#include <cstdint>

namespace diamond {

std::vector<std::string> rows(char letter) {
    // Validate input - comparison between same character types is allowed
    if ((letter < 'A') || (letter > 'Z')) {
        return {};
    }
    
    // Special case for 'A'
    if (letter == 'A') {
        return {"A"};
    }
    
    // Calculate the size of the diamond without character arithmetic
    // We'll build an array of letters to avoid arithmetic on characters
    std::vector<char> letters;
    char current = 'A';
    letters.push_back(current);
    
    while (current != letter) {
        // Increment through the alphabet without arithmetic
        if (current == 'A') {
            current = 'B';
        } else if (current == 'B') {
            current = 'C';
        } else if (current == 'C') {
            current = 'D';
        } else if (current == 'D') {
            current = 'E';
        } else if (current == 'E') {
            current = 'F';
        } else if (current == 'F') {
            current = 'G';
        } else if (current == 'G') {
            current = 'H';
        } else if (current == 'H') {
            current = 'I';
        } else if (current == 'I') {
            current = 'J';
        } else if (current == 'J') {
            current = 'K';
        } else if (current == 'K') {
            current = 'L';
        } else if (current == 'L') {
            current = 'M';
        } else if (current == 'M') {
            current = 'N';
        } else if (current == 'N') {
            current = 'O';
        } else if (current == 'O') {
            current = 'P';
        } else if (current == 'P') {
            current = 'Q';
        } else if (current == 'Q') {
            current = 'R';
        } else if (current == 'R') {
            current = 'S';
        } else if (current == 'S') {
            current = 'T';
        } else if (current == 'T') {
            current = 'U';
        } else if (current == 'U') {
            current = 'V';
        } else if (current == 'V') {
            current = 'W';
        } else if (current == 'W') {
            current = 'X';
        } else if (current == 'X') {
            current = 'Y';
        } else if (current == 'Y') {
            current = 'Z';
        }
        letters.push_back(current);
    }
    
    std::int32_t size = static_cast<std::int32_t>(letters.size());
    
    // Total rows in diamond
    std::int32_t totalRows = ((size * 2) - 1);
    
    // Build the diamond
    std::vector<std::string> lines;
    lines.reserve(static_cast<std::size_t>(totalRows));
    
    // Top half including middle
    for (std::int32_t row = 0; row < size; row++) {
        std::string line;
        std::int32_t totalCols = ((size * 2) - 1);
        
        // Calculate spaces and letter position
        std::int32_t outerSpaces = (size - (row + 1));
        
        if (row == 0) {
            // First row: only one 'A' in the center
            for (std::int32_t col = 0; col < totalCols; col++) {
                if (col == outerSpaces) {
                    line += letters[0];
                } else {
                    line += ' ';
                }
            }
        } else {
            // Other rows: two letters
            std::int32_t innerSpaces = ((row * 2) - 1);
            char rowLetter = letters[static_cast<std::size_t>(row)];
            
            for (std::int32_t col = 0; col < totalCols; col++) {
                if (col == outerSpaces) {
                    line += rowLetter;
                } else if (col == ((outerSpaces + innerSpaces) + 1)) {
                    line += rowLetter;
                } else {
                    line += ' ';
                }
            }
        }
        
        lines.push_back(line);
    }
    
    // Bottom half (mirror of top, excluding middle)
    for (std::int32_t row = (size - 2); row >= 0; row--) {
        lines.push_back(lines[static_cast<std::size_t>(row)]);
    }
    
    return lines;
}

}  // namespace diamond
