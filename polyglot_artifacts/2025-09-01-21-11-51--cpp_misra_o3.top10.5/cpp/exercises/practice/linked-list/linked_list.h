#pragma once

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node {
        T          data;
        Node*      prev;
        Node*      next;

        explicit Node(const T& value, Node* p = nullptr, Node* n = nullptr)
            : data(value), prev(p), next(n) {}
    };

    Node*         head_{nullptr};
    Node*         tail_{nullptr};
    std::uint32_t size_{0U};

    /* helper: remove a single node (does not adjust size_) */
    static void destroy_node(Node* node)
    {
        delete node;
    }

public:
    List() = default;

    /* rule-of-five : copy disabled, move enabled */
    List(const List&)            = delete;
    List& operator=(const List&) = delete;

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_)
    {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other) {
            while (head_ != nullptr) {
                Node* const temp = head_;
                head_            = head_->next;
                destroy_node(temp);
            }
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
        while (head_ != nullptr) {
            Node* const temp = head_;
            head_            = head_->next;
            destroy_node(temp);
        }
    }

    void push(const T& value)
    {
        Node* const new_node = new Node(value, tail_, nullptr);
        if (tail_ == nullptr) {
            head_ = new_node;
        } else {
            tail_->next = new_node;
        }
        tail_ = new_node;
        ++size_;
    }

    T pop()
    {
        if (tail_ == nullptr) {
            throw std::out_of_range("pop on empty List");
        }
        Node* const to_remove = tail_;
        const T     ret_val   = to_remove->data;

        tail_ = tail_->prev;
        if (tail_ == nullptr) {
            head_ = nullptr;
        } else {
            tail_->next = nullptr;
        }

        destroy_node(to_remove);
        --size_;
        return ret_val;
    }

    T shift()
    {
        if (head_ == nullptr) {
            throw std::out_of_range("shift on empty List");
        }
        Node* const to_remove = head_;
        const T     ret_val   = to_remove->data;

        head_ = head_->next;
        if (head_ == nullptr) {
            tail_ = nullptr;
        } else {
            head_->prev = nullptr;
        }

        destroy_node(to_remove);
        --size_;
        return ret_val;
    }

    void unshift(const T& value)
    {
        Node* const new_node = new Node(value, nullptr, head_);
        if (head_ == nullptr) {
            tail_ = new_node;
        } else {
            head_->prev = new_node;
        }
        head_ = new_node;
        ++size_;
    }

    std::uint32_t count() const noexcept
    {
        return size_;
    }

    bool erase(const T& value)
    {
        for (Node* current = head_; current != nullptr; current = current->next) {
            if (current->data == value) {
                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                } else {
                    head_ = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                } else {
                    tail_ = current->prev;
                }

                destroy_node(current);
                --size_;
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
