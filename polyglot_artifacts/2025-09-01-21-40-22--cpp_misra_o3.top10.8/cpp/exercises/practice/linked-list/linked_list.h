#pragma once

#include <cstdint>
#include <memory>
#include <stdexcept>
#include <utility>

namespace linked_list {

template <typename T>
class List
{
private:
    struct Node
    {
        T                 data {};
        std::unique_ptr<Node> next { nullptr };
        Node*             prev { nullptr };

        explicit Node(const T& value) : data(value) {}
    };

    std::unique_ptr<Node> head { nullptr };
    Node*                 tail { nullptr };
    std::uint32_t         element_count { 0U };

    /* helper used by copy-operations */
    void copy_from(const List& other)
    {
        for (Node* cur = other.head.get(); cur != nullptr; cur = cur->next.get())
        {
            push(cur->data);
        }
    }

public:
    List() = default;

    /* deep copy */
    List(const List& other)
    {
        copy_from(other);
    }

    List& operator=(const List& other)
    {
        if (this != &other)
        {
            clear();
            copy_from(other);
        }
        return *this;
    }

    /* move operations */
    List(List&& other) noexcept
        : head(std::move(other.head)),
          tail(other.tail),
          element_count(other.element_count)
    {
        other.tail           = nullptr;
        other.element_count  = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
            clear();
            head            = std::move(other.head);
            tail            = other.tail;
            element_count   = other.element_count;

            other.tail           = nullptr;
            other.element_count  = 0U;
        }
        return *this;
    }

    ~List() = default;

    void clear()
    {
        while (element_count != 0U)
        {
            (void)pop();
        }
    }

    std::uint32_t count() const noexcept
    {
        return element_count;
    }

    void push(const T& value)
    {
        auto  new_node = std::make_unique<Node>(value);
        Node* raw_ptr  = new_node.get();

        if (tail == nullptr)
        {
            head = std::move(new_node);
            tail = raw_ptr;
        }
        else
        {
            tail->next = std::move(new_node);
            tail->next->prev = tail;
            tail = raw_ptr;
        }
        ++element_count;
    }

    void unshift(const T& value)
    {
        auto new_node = std::make_unique<Node>(value);

        if (head == nullptr)
        {
            tail = new_node.get();
        }
        else
        {
            head->prev = new_node.get();
            new_node->next = std::move(head);
        }
        head = std::move(new_node);
        ++element_count;
    }

    T pop()
    {
        if (tail == nullptr)
        {
            throw std::out_of_range("pop on empty list");
        }

        T   value = tail->data;
        if (tail->prev == nullptr)
        {
            head.reset();
            tail = nullptr;
        }
        else
        {
            std::unique_ptr<Node> to_delete { tail->prev->next.release() };
            tail = tail->prev;
            tail->next = nullptr;
        }
        --element_count;
        return value;
    }

    T shift()
    {
        if (head == nullptr)
        {
            throw std::out_of_range("shift on empty list");
        }

        T value = head->data;
        if (head->next == nullptr)
        {
            head.reset();
            tail = nullptr;
        }
        else
        {
            head = std::move(head->next);
            head->prev = nullptr;
        }
        --element_count;
        return value;
    }

    bool erase(const T& value)
    {
        for (Node* cur = head.get(); cur != nullptr; cur = cur->next.get())
        {
            if (cur->data == value)
            {
                if (cur->prev == nullptr)
                {
                    (void)shift();
                }
                else if (cur->next == nullptr)
                {
                    (void)pop();
                }
                else
                {
                    std::unique_ptr<Node> to_delete { cur->prev->next.release() };
                    cur->prev->next = std::move(to_delete->next);
                    cur->prev->next->prev = cur->prev;
                    --element_count;
                }
                return true;
            }
        }
        return false;
    }
};

}  // namespace linked_list
