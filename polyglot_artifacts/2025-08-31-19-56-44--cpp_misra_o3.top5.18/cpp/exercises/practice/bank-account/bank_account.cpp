#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept = default;

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open) {
        throw std::logic_error("Account already open");
    }
    m_balance = static_cast<std::int32_t>(0);
    m_open    = true;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::logic_error("Account already closed");
    }
    m_balance = static_cast<std::int32_t>(0);
    m_open    = false;
}

void Bankaccount::deposit(std::int32_t amount)
{
    if (amount < static_cast<std::int32_t>(0)) {
        throw std::invalid_argument("Deposit amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::logic_error("Account is closed");
    }

    m_balance += amount;
}

void Bankaccount::withdraw(std::int32_t amount)
{
    if (amount < static_cast<std::int32_t>(0)) {
        throw std::invalid_argument("Withdraw amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::logic_error("Account is closed");
    }
    if (m_balance < amount) {
        throw std::logic_error("Insufficient funds");
    }

    m_balance -= amount;
}

std::int32_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::logic_error("Account is closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
