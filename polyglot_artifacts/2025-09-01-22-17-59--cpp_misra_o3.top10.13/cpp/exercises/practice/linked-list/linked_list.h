#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T       data;
        Node*   prev;
        Node*   next;

        explicit Node(const T& value) : data(value), prev(nullptr), next(nullptr) {}
        explicit Node(T&& value)      : data(std::move(value)), prev(nullptr), next(nullptr) {}
    };

    Node*       head_{nullptr};
    Node*       tail_{nullptr};
    std::size_t size_{0U};

    void clear() noexcept
    {
        Node* current{head_};
        while (current != nullptr) {
            Node* const nextNode{current->next};
            delete current;
            current = nextNode;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

public:
    List() = default;

    List(const List& other)
        : head_{nullptr},
          tail_{nullptr},
          size_{0U}
    {
        Node* current{other.head_};
        while (current != nullptr) {
            push(current->data);
            current = current->next;
        }
    }

    List& operator=(const List& other)
    {
        if (this != &other) {
            clear();
            Node* current{other.head_};
            while (current != nullptr) {
                push(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    List(List&& other) noexcept
        : head_{other.head_}, tail_{other.tail_}, size_{other.size_}
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            clear();
            head_       = other.head_;
            tail_       = other.tail_;
            size_       = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    ~List()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* const node{new Node{value}};
        if (size_ == 0U) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev   = tail_;
            tail_->next  = node;
            tail_        = node;
        }
        ++size_;
    }

    void push(T&& value)
    {
        Node* const node{new Node{std::move(value)}};
        if (size_ == 0U) {
            head_ = node;
            tail_ = node;
        } else {
            node->prev   = tail_;
            tail_->next  = node;
            tail_        = node;
        }
        ++size_;
    }

    T pop()
    {
        if (size_ == 0U) {
            throw std::out_of_range("pop on empty list");
        }
        Node* const node{tail_};
        tail_ = tail_->prev;
        if (tail_ != nullptr) {
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
        }
        T value{std::move(node->data)};
        delete node;
        --size_;
        return value;
    }

    void unshift(const T& value)
    {
        Node* const node{new Node{value}};
        if (size_ == 0U) {
            head_ = node;
            tail_ = node;
        } else {
            node->next   = head_;
            head_->prev  = node;
            head_        = node;
        }
        ++size_;
    }

    void unshift(T&& value)
    {
        Node* const node{new Node{std::move(value)}};
        if (size_ == 0U) {
            head_ = node;
            tail_ = node;
        } else {
            node->next   = head_;
            head_->prev  = node;
            head_        = node;
        }
        ++size_;
    }

    T shift()
    {
        if (size_ == 0U) {
            throw std::out_of_range("shift on empty list");
        }
        Node* const node{head_};
        head_ = head_->next;
        if (head_ != nullptr) {
            head_->prev = nullptr;
        } else {
            tail_ = nullptr;
        }
        T value{std::move(node->data)};
        delete node;
        --size_;
        return value;
    }

    std::size_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        Node* current{head_};
        while (current != nullptr) {
            if (current->data == value) {
                Node* const prevNode{current->prev};
                Node* const nextNode{current->next};

                if (prevNode != nullptr) {
                    prevNode->next = nextNode;
                } else {
                    head_ = nextNode;
                }

                if (nextNode != nullptr) {
                    nextNode->prev = prevNode;
                } else {
                    tail_ = prevNode;
                }

                delete current;
                --size_;
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
