#pragma once

#include <cstddef>      // for std::size_t
#include <cstdint>      // fixed-width integer types
#include <stdexcept>    // for std::out_of_range
#include <utility>      // for std::move

namespace linked_list {

template <typename T>
class List
{
private:
    struct Node
    {
        T        data {};
        Node*    prev {nullptr};
        Node*    next {nullptr};

        explicit Node(const T& value) : data(value) {}
        explicit Node(T&& value) : data(std::move(value)) {}
    };

    Node*       m_head {nullptr};
    Node*       m_tail {nullptr};
    std::size_t m_size {0U};

    void unlink(Node* node) noexcept
    {
        if (node == nullptr)
        {
            return;
        }

        if (node->prev != nullptr)
        {
            node->prev->next = node->next;
        }
        else
        {
            m_head = node->next;
        }

        if (node->next != nullptr)
        {
            node->next->prev = node->prev;
        }
        else
        {
            m_tail = node->prev;
        }

        delete node;
        --m_size;
    }

    /* clear entire list */
    void clear() noexcept
    {
        while (m_head != nullptr)
        {
            Node* const next_node {m_head->next};
            delete m_head;
            m_head = next_node;
        }
        m_tail = nullptr;
        m_size = 0U;
    }

public:
    List() = default;

    ~List()
    {
        clear();
    }

    void push(const T& value)
    {
        Node* const new_node {new Node(value)};

        new_node->prev = m_tail;

        if (m_tail != nullptr)
        {
            m_tail->next = new_node;
        }
        else
        {
            m_head = new_node;
        }

        m_tail = new_node;
        ++m_size;
    }

    void push(T&& value)
    {
        Node* const new_node {new Node(std::move(value))};

        new_node->prev = m_tail;

        if (m_tail != nullptr)
        {
            m_tail->next = new_node;
        }
        else
        {
            m_head = new_node;
        }

        m_tail = new_node;
        ++m_size;
    }

    T pop()
    {
        if (m_tail == nullptr)
        {
            throw std::out_of_range("pop on empty list");
        }

        Node* const node_to_remove {m_tail};
        T           value           {std::move(node_to_remove->data)};

        m_tail = node_to_remove->prev;

        if (m_tail != nullptr)
        {
            m_tail->next = nullptr;
        }
        else
        {
            m_head = nullptr;
        }

        delete node_to_remove;
        --m_size;

        return value;
    }

    void unshift(const T& value)
    {
        Node* const new_node {new Node(value)};

        new_node->next = m_head;

        if (m_head != nullptr)
        {
            m_head->prev = new_node;
        }
        else
        {
            m_tail = new_node;
        }

        m_head = new_node;
        ++m_size;
    }

    void unshift(T&& value)
    {
        Node* const new_node {new Node(std::move(value))};

        new_node->next = m_head;

        if (m_head != nullptr)
        {
            m_head->prev = new_node;
        }
        else
        {
            m_tail = new_node;
        }

        m_head = new_node;
        ++m_size;
    }

    T shift()
    {
        if (m_head == nullptr)
        {
            throw std::out_of_range("shift on empty list");
        }

        Node* const node_to_remove {m_head};
        T           value           {std::move(node_to_remove->data)};

        m_head = node_to_remove->next;

        if (m_head != nullptr)
        {
            m_head->prev = nullptr;
        }
        else
        {
            m_tail = nullptr;
        }

        delete node_to_remove;
        --m_size;

        return value;
    }

    bool erase(const T& value)
    {
        Node* current {m_head};

        while (current != nullptr)
        {
            if (current->data == value)
            {
                unlink(current);
                return true;
            }
            current = current->next;
        }

        return false;
    }

    [[nodiscard]] std::size_t count() const noexcept
    {
        return m_size;
    }

    [[nodiscard]] std::size_t size() const noexcept
    {
        return m_size;
    }

    // Copy semantics
    List(const List& other) :
        m_head(nullptr),
        m_tail(nullptr),
        m_size(0U)
    {
        Node* current {other.m_head};
        while (current != nullptr)
        {
            push(current->data);
            current = current->next;
        }
    }

    List& operator=(const List& other)
    {
        if (this != &other)
        {
            clear();
            Node* current {other.m_head};
            while (current != nullptr)
            {
                push(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    // Move semantics
    List(List&& other) noexcept :
        m_head(other.m_head),
        m_tail(other.m_tail),
        m_size(other.m_size)
    {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_size = 0U;
    }

    List& operator=(List&& other) noexcept
    {
        if (this != &other)
        {
            /* release current resources */
            clear();

            /* take ownership from source */
            m_head       = other.m_head;
            m_tail       = other.m_tail;
            m_size       = other.m_size;

            /* leave source in valid state */
            other.m_head = nullptr;
            other.m_tail = nullptr;
            other.m_size = 0U;
        }
        return *this;
    }
};

}  // namespace linked_list
