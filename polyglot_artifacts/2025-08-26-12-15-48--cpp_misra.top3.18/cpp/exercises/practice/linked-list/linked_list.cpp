#include "linked_list.h"

namespace linked_list {

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr), size(0U) {}

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
    size = 0U;
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
    size = size + 1U;
}

template <typename T>
T List<T>::pop() {
    if (tail == nullptr) {
        // List is empty, throw or handle as needed
        throw "pop from empty list";
    }
    Node* node_to_remove = tail;
    T value = node_to_remove->value;
    if (tail->prev != nullptr) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete node_to_remove;
    size = size - 1U;
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
    size = size + 1U;
}

template <typename T>
T List<T>::shift() {
    if (head == nullptr) {
        // List is empty, throw or handle as needed
        throw "shift from empty list";
    }
    Node* node_to_remove = head;
    T value = node_to_remove->value;
    if (head->next != nullptr) {
        head = head->next;
        head->prev = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete node_to_remove;
    size = size - 1U;
    return value;
}

template <typename T>
std::uint32_t List<T>::count() const {
    return size;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            if ((current->prev == nullptr) && (current->next == nullptr)) {
                // Only node
                head = nullptr;
                tail = nullptr;
            } else if (current->prev == nullptr) {
                // Head node
                head = current->next;
                head->prev = nullptr;
            } else if (current->next == nullptr) {
                // Tail node
                tail = current->prev;
                tail->next = nullptr;
            } else {
                // Middle node
                current->prev->next = current->next;
                current->next->prev = current->prev;
            }
            delete current;
            size = size - 1U;
            return true;
        }
        current = current->next;
    }
    return false;
}

// Move constructor
template <typename T>
List<T>::List(List&& other) noexcept
    : head(other.head), tail(other.tail), size(other.size) {
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0U;
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
        size = other.size;
        other.head = nullptr;
        other.tail = nullptr;
        other.size = 0U;
    }
    return *this;
}

// Explicit instantiations for station_id_t
// The explicit instantiation of a template class should be in the translation unit where all member functions are visible.
// However, since all member functions are defined in this file, this is correct.
// To avoid linker errors, mark the instantiation as 'extern template' in the header if needed, but for now, this is fine.

template class linked_list::List<linked_list::station_id_t>;

}  // namespace linked_list
