#include <stdexcept>

namespace linked_list {

template <typename T>
List<T>::~List() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

template <typename T>
void List<T>::push(const T& value) {
    Node* new_node = new Node(value);
    if (tail == nullptr) {
        head = tail = new_node;
    } else {
        tail->next = new_node;
        new_node->prev = tail;
        tail = new_node;
    }
    ++list_count;
}

template <typename T>
T List<T>::pop() {
    if (tail == nullptr) {
        throw std::runtime_error("Cannot pop from empty list");
    }
    Node* temp = tail;
    T data = temp->data;
    tail = tail->prev;
    if (tail != nullptr) {
        tail->next = nullptr;
    } else {
        head = nullptr;
    }
    delete temp;
    --list_count;
    return data;
}

template <typename T>
T List<T>::shift() {
    if (head == nullptr) {
        throw std::runtime_error("Cannot shift from empty list");
    }
    Node* temp = head;
    T data = temp->data;
    head = head->next;
    if (head != nullptr) {
        head->prev = nullptr;
    } else {
        tail = nullptr;
    }
    delete temp;
    --list_count;
    return data;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* new_node = new Node(value);
    if (head == nullptr) {
        head = tail = new_node;
    } else {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    ++list_count;
}

template <typename T>
std::size_t List<T>::count() const {
    return list_count;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) {
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
            --list_count;
            return true;
        }
        current = current->next;
    }
    return false;
}

}  // namespace linked_list
