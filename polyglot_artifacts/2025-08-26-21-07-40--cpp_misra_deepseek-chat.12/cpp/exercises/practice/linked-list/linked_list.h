#pragma once
#include <cstdint>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* next;
        Node* prev;
        explicit Node(const T& val) : value(val), next(nullptr), prev(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    std::uint32_t list_size;
    
public:
    List() : head(nullptr), tail(nullptr), list_size(0U) {}
    ~List();
    void push(const T& value);
    T pop();
    T shift();
    void unshift(const T& value);
    std::uint32_t count() const { return list_size; }
    bool erase(const T& value);
};

}  // namespace linked_list
