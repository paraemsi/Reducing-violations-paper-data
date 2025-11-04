#pragma once
#include <cstdint>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T data;
        Node* prev;
        Node* next;
        Node(const T& val) : data(val), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    std::size_t list_count;

public:
    List() : head(nullptr), tail(nullptr), list_count(0) {}
    ~List();
    
    void push(const T& value);
    T pop();
    T shift();
    void unshift(const T& value);
    std::size_t count() const;
    bool erase(const T& value);
};

}  // namespace linked_list

#include "linked_list.tpp"
