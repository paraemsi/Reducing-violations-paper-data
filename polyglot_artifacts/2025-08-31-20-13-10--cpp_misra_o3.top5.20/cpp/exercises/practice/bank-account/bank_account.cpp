#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_is_open(false),
      m_balance(static_cast<std::int64_t>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    } else {
        m_is_open = true;
        m_balance = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account not open");
    } else {
        m_is_open = false;
    }
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account not open");
    } else {
        return m_balance;
    }
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Deposit amount must be non-negative");
    } else {
        m_balance += amount;
    }
}

void Bankaccount::withdraw(std::int64_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    if (amount < static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Withdraw amount must be non-negative");
    }
    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    } else {
        m_balance -= amount;
    }
}

}  // namespace Bankaccount
