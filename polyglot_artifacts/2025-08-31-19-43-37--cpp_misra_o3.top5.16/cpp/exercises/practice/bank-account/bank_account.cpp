#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_is_open(false),
      m_balance(static_cast<money_t>(0)) { }

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    }
    m_balance = static_cast<money_t>(0);
    m_is_open = true;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account already closed");
    }
    m_is_open = false;
    m_balance = static_cast<money_t>(0);
}

void Bankaccount::deposit(money_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < static_cast<money_t>(0)) {
        throw std::invalid_argument("Deposit amount must be non-negative");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(money_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < static_cast<money_t>(0)) {
        throw std::invalid_argument("Withdrawal amount must be non-negative");
    }
    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

money_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
