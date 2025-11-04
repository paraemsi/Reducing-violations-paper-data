#include "bank_account.h"

#include <stdexcept>   // std::logic_error, std::runtime_error
#include <mutex>       // std::lock_guard

namespace Bankaccount {

Bankaccount::Bankaccount() : m_open(false), m_balance(0) {}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open) {
        throw std::runtime_error("Account already open");
    } else {
        m_open   = true;
        m_balance = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account already closed");
    } else {
        m_open   = false;
        m_balance = static_cast<std::int64_t>(0);
    }
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    } else {
        return m_balance;
    }
}

void Bankaccount::deposit(std::int64_t amount)
{
    if (amount <= static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Deposit amount must be positive");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    } else {
        m_balance += amount;
    }
}

void Bankaccount::withdraw(std::int64_t amount)
{
    if (amount <= static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Withdraw amount must be positive");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    } else {
        if (m_balance < amount) {
            throw std::runtime_error("Insufficient funds");
        } else {
            m_balance -= amount;
        }
    }
}

}  // namespace Bankaccount
