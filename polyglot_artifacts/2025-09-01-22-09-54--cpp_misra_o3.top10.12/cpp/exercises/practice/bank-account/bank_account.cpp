#include "bank_account.h"

#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_open(false),
      m_balance(static_cast<std::int64_t>(0)) {}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    /* Disallow opening an already open account */
    if (m_open) {
        throw std::runtime_error("Account already open");
    }
    m_open    = true;
    m_balance = static_cast<std::int64_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account already closed");
    }
    m_open = false;
}

void Bankaccount::deposit(std::int64_t amount)
{
    if (amount <= static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount)
{
    if (amount <= static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Withdraw amount must be positive");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    }
    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
