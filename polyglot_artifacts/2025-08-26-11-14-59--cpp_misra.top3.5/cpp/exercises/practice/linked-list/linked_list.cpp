#include "linked_list.h"
#include <stdexcept>

namespace linked_list {

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), node_count(0U) {}

template <typename T>
List<T>::~List() {
    Node* current = head;
    while (current != nullptr) {
        Node* next_node = current->next;
        delete current;
        current = next_node;
    }
    head = nullptr;
    tail = nullptr;
    node_count = 0U;
}

template <typename T>
void List<T>::push(const T& value) {
    Node* new_node = new Node(value);
    if (tail == nullptr) {
        head = new_node;
        tail = new_node;
    } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    node_count = node_count + 1U;
}

template <typename T>
T List<T>::pop() {
    if (tail == nullptr) {
        throw std::out_of_range("List is empty");
    }
    Node* node_to_remove = tail;
    T value = node_to_remove->value;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete node_to_remove;
    node_count = node_count - 1U;
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* new_node = new Node(value);
    if (head == nullptr) {
        head = new_node;
        tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    node_count = node_count + 1U;
}

template <typename T>
T List<T>::shift() {
    if (head == nullptr) {
        throw std::out_of_range("List is empty");
    }
    Node* node_to_remove = head;
    T value = node_to_remove->value;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete node_to_remove;
    node_count = node_count - 1U;
    return value;
}

template <typename T>
std::size_t List<T>::count() const {
    return node_count;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            if (current->prev != nullptr) {
                current->prev->next = current->next;
            } else {
                head = current->next;
            }
            if (current->next != nullptr) {
                current->next->prev = current->prev;
            } else {
                tail = current->prev;
            }
            delete current;
            node_count = node_count - 1U;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Move constructor
template <typename T>
List<T>::List(List&& other) noexcept
    : head(other.head), tail(other.tail), node_count(other.node_count) {
    other.head = nullptr;
    other.tail = nullptr;
    other.node_count = 0U;
}

// Move assignment
template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        // Clean up current list
        Node* current = head;
        while (current != nullptr) {
            Node* next_node = current->next;
            delete current;
            current = next_node;
        }
        head = other.head;
        tail = other.tail;
        node_count = other.node_count;
        other.head = nullptr;
        other.tail = nullptr;
        other.node_count = 0U;
    }
    return *this;
}

}  // namespace linked_list

// Explicit instantiations for common types (add more as needed)
template class linked_list::List<std::int32_t>;
template class linked_list::List<std::uint32_t>;
template class linked_list::List<std::int64_t>;
template class linked_list::List<std::uint64_t>;
