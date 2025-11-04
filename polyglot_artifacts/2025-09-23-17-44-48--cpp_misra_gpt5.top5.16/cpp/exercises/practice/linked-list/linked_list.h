#pragma once

#include <cstdint>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List {
private:
    struct Node final {
        T value;
        Node* prev;
        Node* next;

        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}
        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    Node* head_{nullptr};
    Node* tail_{nullptr};
    std::uint32_t size_{0U};

    void clear() noexcept {
        Node* current = head_;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
        head_ = nullptr;
        tail_ = nullptr;
        size_ = 0U;
    }

    void link_back(Node* node) {
        node->prev = tail_;
        node->next = nullptr;
        if ((tail_ != nullptr)) {
            tail_->next = node;
        } else {
            head_ = node;
        }
        tail_ = node;
        ++size_;
    }

    void link_front(Node* node) {
        node->prev = nullptr;
        node->next = head_;
        if ((head_ != nullptr)) {
            head_->prev = node;
        } else {
            tail_ = node;
        }
        head_ = node;
        ++size_;
    }

    static void unlink_node(Node* node, Node*& head, Node*& tail, std::uint32_t& size) {
        Node* const prev = node->prev;
        Node* const next = node->next;

        if ((prev != nullptr)) {
            prev->next = next;
        } else {
            head = next;
        }

        if ((next != nullptr)) {
            next->prev = prev;
        } else {
            tail = prev;
        }

        delete node;
        if (size > 0U) {
            --size;
        }
    }

public:
    List() noexcept = default;

    ~List() noexcept {
        clear();
    }

    List(const List& other) : head_(nullptr), tail_(nullptr), size_(0U) {
        Node* current = other.head_;
        while (current != nullptr) {
            push(current->value);
            current = current->next;
        }
    }

    List& operator=(const List& other) {
        if ((this != &other)) {
            clear();
            Node* current = other.head_;
            while (current != nullptr) {
                push(current->value);
                current = current->next;
            }
        }
        return *this;
    }

    List(List&& other) noexcept
        : head_(other.head_), tail_(other.tail_), size_(other.size_) {
        other.head_ = nullptr;
        other.tail_ = nullptr;
        other.size_ = 0U;
    }

    List& operator=(List&& other) noexcept {
        if ((this != &other)) {
            clear();
            head_ = other.head_;
            tail_ = other.tail_;
            size_ = other.size_;
            other.head_ = nullptr;
            other.tail_ = nullptr;
            other.size_ = 0U;
        }
        return *this;
    }

    std::uint32_t count() const noexcept {
        return size_;
    }

    void push(const T& value) {
        Node* node = new Node(value);
        link_back(node);
    }

    void push(T&& value) {
        Node* node = new Node(std::move(value));
        link_back(node);
    }

    T pop() {
        if ((size_ == 0U)) {
            throw std::out_of_range("pop on empty List");
        }
        Node* node = tail_;
        T out = std::move(node->value);
        if (node->prev != nullptr) {
            tail_ = node->prev;
            tail_->next = nullptr;
        } else {
            head_ = nullptr;
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return out;
    }

    void unshift(const T& value) {
        Node* node = new Node(value);
        link_front(node);
    }

    void unshift(T&& value) {
        Node* node = new Node(std::move(value));
        link_front(node);
    }

    T shift() {
        if ((size_ == 0U)) {
            throw std::out_of_range("shift on empty List");
        }
        Node* node = head_;
        T out = std::move(node->value);
        if (node->next != nullptr) {
            head_ = node->next;
            head_->prev = nullptr;
        } else {
            head_ = nullptr;
            tail_ = nullptr;
        }
        delete node;
        --size_;
        return out;
    }

    bool erase(const T& value) {
        Node* current = head_;
        while (current != nullptr) {
            if ((current->value == value)) {
                unlink_node(current, head_, tail_, size_);
                return true;
            }
            current = current->next;
        }
        return false;
    }
};

}  // namespace linked_list
