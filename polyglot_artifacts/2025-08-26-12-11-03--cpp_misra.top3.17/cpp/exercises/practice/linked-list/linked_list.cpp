#include "linked_list.h"

namespace linked_list {

template <typename T>
List<T>::~List() {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
    tail = nullptr;
    sz = 0U;
}

template <typename T>
List<T>::List(List&& other) noexcept
    : head(other.head), tail(other.tail), sz(other.sz) {
    other.head = nullptr;
    other.tail = nullptr;
    other.sz = 0U;
}

template <typename T>
List<T>& List<T>::operator=(List&& other) noexcept {
    if (this != &other) {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
        head = other.head;
        tail = other.tail;
        sz = other.sz;
        other.head = nullptr;
        other.tail = nullptr;
        other.sz = 0U;
    }
    return *this;
}

template <typename T>
void List<T>::push(const T& value) {
    Node* node = new Node(value);
    if (tail == nullptr) {
        head = node;
        tail = node;
    } else {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    sz = (sz + 1U);
}

template <typename T>
T List<T>::pop() {
    if (tail == nullptr) {
        throw "List is empty";
    }
    Node* node = tail;
    T value = node->value;
    if (tail->prev != nullptr) {
        tail = tail->prev;
        tail->next = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete node;
    sz = (sz - 1U);
    return value;
}

template <typename T>
void List<T>::unshift(const T& value) {
    Node* node = new Node(value);
    if (head == nullptr) {
        head = node;
        tail = node;
    } else {
        node->next = head;
        head->prev = node;
        head = node;
    }
    sz = (sz + 1U);
}

template <typename T>
T List<T>::shift() {
    if (head == nullptr) {
        throw "List is empty";
    }
    Node* node = head;
    T value = node->value;
    if (head->next != nullptr) {
        head = head->next;
        head->prev = nullptr;
    } else {
        head = nullptr;
        tail = nullptr;
    }
    delete node;
    sz = (sz - 1U);
    return value;
}

template <typename T>
std::size_t List<T>::count() const {
    return sz;
}

template <typename T>
bool List<T>::erase(const T& value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->value == value) {
            if ((current->prev != nullptr) && (current->next != nullptr)) {
                current->prev->next = current->next;
                current->next->prev = current->prev;
            } else if (current->prev == nullptr) {
                // head node
                head = current->next;
                if (head != nullptr) {
                    head->prev = nullptr;
                }
            } else if (current->next == nullptr) {
                // tail node
                tail = current->prev;
                if (tail != nullptr) {
                    tail->next = nullptr;
                }
            }
            delete current;
            sz = (sz - 1U);
            if (sz == 0U) {
                head = nullptr;
                tail = nullptr;
            }
            return true;
        }
        current = current->next;
    }
    return false;
}

// Explicit instantiations for station_id_t (for typical test cases)
template class linked_list::List<linked_list::station_id_t>;

}  // namespace linked_list
