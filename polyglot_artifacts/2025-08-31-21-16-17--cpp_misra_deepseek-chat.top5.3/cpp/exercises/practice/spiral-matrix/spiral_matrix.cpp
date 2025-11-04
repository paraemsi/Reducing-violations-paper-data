#include "spiral_matrix.h"
#include <vector>
#include <cstdint>

namespace spiral_matrix {

namespace {
    using size_type = std::int32_t;
}

std::vector<std::vector<int>> spiral_matrix(int size) {
    if (size == 0) {
        return {};
    }
    
    // Initialize the matrix with zeros
    std::vector<std::vector<int>> matrix(static_cast<std::vector<std::vector<int>>::size_type>(size), 
                                         std::vector<int>(static_cast<std::vector<int>::size_type>(size), 0));
    
    size_type num = 1;
    size_type top = 0;
    size_type bottom = static_cast<size_type>(size) - 1;
    size_type left = 0;
    size_type right = static_cast<size_type>(size) - 1;
    
    while ((top <= bottom) && (left <= right)) {
        // Fill top row
        for (size_type i = left; i <= right; i++) {
            matrix[static_cast<std::vector<std::vector<int>>::size_type>(top)]
                  [static_cast<std::vector<int>::size_type>(i)] = static_cast<int>(num);
            num++;
        }
        top++;
        
        // Fill right column
        for (size_type i = top; i <= bottom; i++) {
            matrix[static_cast<std::vector<std::vector<int>>::size_type>(i)]
                  [static_cast<std::vector<int>::size_type>(right)] = static_cast<int>(num);
            num++;
        }
        right--;
        
        // Fill bottom row
        if (top <= bottom) {
            for (size_type i = right; i >= left; i--) {
                matrix[static_cast<std::vector<std::vector<int>>::size_type>(bottom)]
                      [static_cast<std::vector<int>::size_type>(i)] = static_cast<int>(num);
                num++;
            }
            bottom--;
        }
        
        // Fill left column
        if (left <= right) {
            for (size_type i = bottom; i >= top; i--) {
                matrix[static_cast<std::vector<std::vector<int>>::size_type>(i)]
                      [static_cast<std::vector<int>::size_type>(left)] = static_cast<int>(num);
                num++;
            }
            left++;
        }
    }
    
    return matrix;
}

}  // namespace spiral_matrix
