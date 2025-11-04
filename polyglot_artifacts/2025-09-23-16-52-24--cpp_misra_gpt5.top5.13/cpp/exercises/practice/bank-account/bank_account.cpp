#include "bank_account.h"

#include <limits>
#include <stdexcept>
#include <utility>

namespace Bankaccount {

void Bankaccount::open()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_is_open == true) {
        throw std::runtime_error("Account already open");
    } else {
        m_balance = 0;
        m_is_open = true;
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_is_open == false) {
        throw std::runtime_error("Account already closed");
    } else {
        m_is_open = false;
    }
}

Bankaccount::Bankaccount(Bankaccount&& other) noexcept
{
    if (this != &other) {
        std::lock(m_mutex, other.m_mutex);
        std::lock_guard<std::mutex> lock_this(m_mutex, std::adopt_lock);
        std::lock_guard<std::mutex> lock_other(other.m_mutex, std::adopt_lock);
        m_is_open = other.m_is_open;
        m_balance = other.m_balance;
        other.m_is_open = false;
        other.m_balance = static_cast<std::int64_t>(0);
    }
}

Bankaccount& Bankaccount::operator=(Bankaccount&& other) noexcept
{
    if (this != &other) {
        std::lock(m_mutex, other.m_mutex);
        std::lock_guard<std::mutex> lock_this(m_mutex, std::adopt_lock);
        std::lock_guard<std::mutex> lock_other(other.m_mutex, std::adopt_lock);
        m_is_open = other.m_is_open;
        m_balance = other.m_balance;
        other.m_is_open = false;
        other.m_balance = static_cast<std::int64_t>(0);
    }
    return *this;
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_is_open == false) {
        throw std::runtime_error("Account is closed");
    } else {
        if (amount < 0) {
            throw std::runtime_error("Deposit amount must be non-negative");
        } else {
            // Overflow check: balance + amount must not exceed max
            const std::int64_t max_val = (std::numeric_limits<std::int64_t>::max)();
            if (amount > (max_val - m_balance)) {
                throw std::overflow_error("Deposit would overflow balance");
            } else {
                m_balance = (m_balance + amount);
            }
        }
    }
}

void Bankaccount::withdraw(std::int64_t amount)
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_is_open == false) {
        throw std::runtime_error("Account is closed");
    } else {
        if (amount < 0) {
            throw std::runtime_error("Withdraw amount must be non-negative");
        } else {
            if (amount > m_balance) {
                throw std::runtime_error("Insufficient funds");
            } else {
                m_balance = (m_balance - amount);
            }
        }
    }
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> guard(m_mutex);
    if (m_is_open == false) {
        throw std::runtime_error("Account is closed");
    } else {
        return m_balance;
    }
}

}  // namespace Bankaccount
