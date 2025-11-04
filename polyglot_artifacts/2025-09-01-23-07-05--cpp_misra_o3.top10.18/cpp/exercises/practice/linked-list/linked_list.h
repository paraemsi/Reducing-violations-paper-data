#pragma once

#include <cstdint>
#include <stdexcept>
#include <utility>
#include <iterator>
#include <cstddef>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {                          // Node must be defined before iterator
        explicit Node(const T& value) : data(value) {}

        T data;
        Node* prev {nullptr};
        Node* next {nullptr};
    };

public:
    using size_type = std::uint32_t;

    List() = default;
    List(const List& other) {
        for(const T& value : other) {
            push(value);
        }
    }

    List(List&& other) noexcept
        : m_head(other.m_head),
          m_tail(other.m_tail),
          m_size(other.m_size) {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = static_cast<size_type>(0U);
    }

    List& operator=(List other) noexcept {
        swap(other);
        return *this;
    }

    ~List() {
        clear();
    }

    void push(const T& value) {
        Node* const new_node = new Node(value);
        if(m_tail == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            m_tail->next = new_node;
            new_node->prev = m_tail;
            m_tail = new_node;
        }
        ++m_size;
    }

    T pop() {
        if(m_tail == nullptr) {
            throw std::out_of_range("pop from empty list");
        }

        Node* const old_tail = m_tail;
        T value = old_tail->data;

        m_tail = old_tail->prev;
        if(m_tail != nullptr) {
            m_tail->next = nullptr;
        } else {
            m_head = nullptr;
        }

        delete old_tail;
        --m_size;
        return value;
    }

    void unshift(const T& value) {
        Node* const new_node = new Node(value);
        if(m_head == nullptr) {
            m_head = new_node;
            m_tail = new_node;
        } else {
            new_node->next = m_head;
            m_head->prev = new_node;
            m_head = new_node;
        }
        ++m_size;
    }

    T shift() {
        if(m_head == nullptr) {
            throw std::out_of_range("shift from empty list");
        }

        Node* const old_head = m_head;
        T value = old_head->data;

        m_head = old_head->next;
        if(m_head != nullptr) {
            m_head->prev = nullptr;
        } else {
            m_tail = nullptr;
        }

        delete old_head;
        --m_size;
        return value;
    }

    bool erase(const T& value) {
        for(Node* current = m_head; current != nullptr; current = current->next) {
            if(current->data == value) {
                if(current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    m_head = current->next;
                }

                if(current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    m_tail = current->prev;
                }

                delete current;
                --m_size;
                return true;
            }
        }
        return false;
    }

    size_type count() const noexcept {
        return m_size;
    }

    void clear() noexcept {
        while(m_head != nullptr) {
            (void)shift();
        }
    }

    void swap(List& other) noexcept {
        using std::swap;
        swap(m_head, other.m_head);
        swap(m_tail, other.m_tail);
        swap(m_size, other.m_size);
    }

    class iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = T;
        using difference_type = std::ptrdiff_t;
        using pointer = T*;
        using reference = T&;

        explicit iterator(Node* ptr) : m_ptr(ptr) {}

        reference operator*() const {
            return m_ptr->data;
        }

        pointer operator->() const {
            return &(m_ptr->data);
        }

        iterator& operator++() {
            m_ptr = m_ptr->next;
            return *this;
        }

        iterator operator++(int) {
            iterator temp(*this);
            ++(*this);
            return temp;
        }

        bool operator==(const iterator& other) const noexcept {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const iterator& other) const noexcept {
            return m_ptr != other.m_ptr;
        }

    private:
        Node* m_ptr;
    };

    iterator begin() noexcept {
        return iterator(m_head);
    }

    iterator begin() const noexcept {
        return iterator(m_head);
    }

    iterator end() noexcept {
        return iterator(nullptr);
    }

    iterator end() const noexcept {
        return iterator(nullptr);
    }

private:

    Node* m_head {nullptr};
    Node* m_tail {nullptr};
    size_type m_size {static_cast<size_type>(0U)};
};

}  // namespace linked_list
