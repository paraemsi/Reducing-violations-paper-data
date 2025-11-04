#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_isOpen) {
        throw std::runtime_error("Account already open");
    } else {
        m_isOpen  = true;
        m_balance = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_isOpen) {
        throw std::runtime_error("Account already closed");
    } else {
        m_isOpen = false;
    }
}

void Bankaccount::deposit(std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Deposit amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_isOpen) {
        throw std::runtime_error("Account is closed");
    } else {
        m_balance += amount;
    }
}

void Bankaccount::withdraw(std::int64_t amount)
{
    if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Withdraw amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_isOpen) {
        throw std::runtime_error("Account is closed");
    } else if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    } else {
        m_balance -= amount;
    }
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_isOpen) {
        throw std::runtime_error("Account is closed");
    } else {
        return m_balance;
    }
}

}  // namespace Bankaccount
