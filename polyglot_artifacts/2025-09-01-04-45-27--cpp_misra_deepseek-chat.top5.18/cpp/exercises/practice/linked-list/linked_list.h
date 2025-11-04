#pragma once
#include <cstdint>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        explicit Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    std::uint32_t size_;
    
public:
    List();
    ~List();
    
    void push(const T& value);
    T pop();
    T shift();
    void unshift(const T& value);
    std::uint32_t count() const;
    bool erase(const T& value);
};

}  // namespace linked_list
