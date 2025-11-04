#include "linked_list.h"

namespace linked_list {

template <typename T>
List<T>::~List() {
    Node* current = head;
    while(current != nullptr) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
    head = nullptr;
    tail = nullptr;
    sz = 0U;
}

template <typename T>
void List<T>::push(const T& value) {
    Node* newNode = new Node(value);
    if(tail == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    sz = sz + 1U;
}

template <typename T>
T List<T>::pop() {
    if(tail == nullptr) {
        throw "List is empty";
    }
    Node* nodeToRemove = tail;
    T value = nodeToRemove->value;
    if(tail->prev != nullptr) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete nodeToRemove;
    sz = sz - 1U;
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* newNode = new Node(value);
    if(head == nullptr) {
        head = newNode;
        tail = newNode;
    } else {
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    sz = sz + 1U;
}

template <typename T>
T List<T>::shift() {
    if(head == nullptr) {
        throw "List is empty";
    }
    Node* nodeToRemove = head;
    T value = nodeToRemove->value;
    if(head->next != nullptr) {
        head = head->next;
        head->prev = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete nodeToRemove;
    sz = sz - 1U;
    return value;
}

template <typename T>
std::size_t List<T>::count() const {
    return sz;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while(current != nullptr) {
        if(current->value == value) {
            if(current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if(current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            sz = sz - 1U;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Move constructor
template <typename T>
List<T>::List(List&& other) noexcept
    : head(other.head), tail(other.tail), sz(other.sz) {
    other.head = nullptr;
    other.tail = nullptr;
    other.sz = 0U;
}

// Move assignment
template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if(this != &other) {
        this->~List();
        head = other.head;
        tail = other.tail;
        sz = other.sz;
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0U;
    }
    return *this;
}

}  // namespace linked_list
