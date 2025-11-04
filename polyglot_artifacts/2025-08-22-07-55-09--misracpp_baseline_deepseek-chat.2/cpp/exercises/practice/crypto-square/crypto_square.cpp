#include "crypto_square.h"
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
#include <cmath>
#include <stdexcept>

using namespace std;

namespace crypto_square {

cipher::cipher(const string& text) {
    // Normalize the input text
    for (char c : text) {
        if (isalnum(c)) {
            normalized_text += tolower(c);
        }
    }
}

string cipher::normalized_plain_text() const {
    return normalized_text;
}

vector<string> cipher::plain_text_segments() const {
    vector<string> segments;
    int c = determine_columns();
    int length = normalized_text.size();
    
    for (int i = 0; i < length; i += c) {
        segments.push_back(normalized_text.substr(i, c));
    }
    return segments;
}

string cipher::cipher_text() const {
    string result;
    int c = determine_columns();
    int r = determine_rows();
    
    // For each column, read down the rows
    for (int col = 0; col < c; col++) {
        for (int row = 0; row < r; row++) {
            size_t index = row * c + col;
            if (index < normalized_text.size()) {
                result += normalized_text[index];
            }
            // No padding for cipher_text()
        }
    }
    return result;
}

string cipher::normalized_cipher_text() const {
    string result;
    int c = determine_columns();
    int r = determine_rows();
    
    // Read column-wise to build the encoded text
    // For each column, read each row
    for (int col = 0; col < c; col++) {
        for (int row = 0; row < r; row++) {
            size_t index = row * c + col;
            if (index < normalized_text.size()) {
                result += normalized_text[index];
            } else {
                result += ' ';
            }
        }
        // Add space between chunks, but not after the last one
        if (col < c - 1) {
            result += ' ';
        }
    }
    return result;
}

int cipher::determine_columns() const {
    size_t length = normalized_text.size();
    if (length == 0) return 0;
    
    // Find the smallest c that satisfies the conditions
    for (int c = 1; ; c++) {
        int r = (length + c - 1) / c; // This is ceiling(length/c)
        if (c >= r && (c - r) <= 1) {
            return c;
        }
    }
}

int cipher::determine_rows() const {
    size_t length = normalized_text.size();
    if (length == 0) return 0;
    
    int c = determine_columns();
    // Number of rows is the ceiling of length/c
    return (length + c - 1) / c;
}

}  // namespace crypto_square
