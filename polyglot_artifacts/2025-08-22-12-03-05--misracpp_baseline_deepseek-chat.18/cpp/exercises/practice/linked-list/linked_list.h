#pragma once

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T value;
        Node* prev;
        Node* next;
        Node(const T& val) : value(val), prev(nullptr), next(nullptr) {}
    };
    
    Node* head;
    Node* tail;
    int num_elements;
    
public:
    List();
    ~List();
    void push(const T& value);
    T pop();
    T shift();
    void unshift(const T& value);
    int count() const;
    bool erase(const T& value);
};

}  // namespace linked_list
