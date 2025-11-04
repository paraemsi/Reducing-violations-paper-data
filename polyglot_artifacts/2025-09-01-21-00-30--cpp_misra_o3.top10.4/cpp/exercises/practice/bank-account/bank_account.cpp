#include "bank_account.h"

namespace Bankaccount {

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock {m_mutex};
    if (m_is_open) {
        throw std::runtime_error("Account already open");
    }
    m_is_open  = true;
    m_balance  = static_cast<money_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock {m_mutex};
    if (!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    m_is_open = false;
}

void Bankaccount::deposit(money_t amount)
{
    std::lock_guard<std::mutex> lock {m_mutex};
    if (!m_is_open) {
        throw std::logic_error("Account not open");
    }
    if (amount < static_cast<money_t>(0)) {
        throw std::runtime_error("Deposit amount must be non-negative");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(money_t amount)
{
    std::lock_guard<std::mutex> lock {m_mutex};
    if (!m_is_open) {
        throw std::logic_error("Account not open");
    }
    if (amount < static_cast<money_t>(0)) {
        throw std::runtime_error("Withdrawal amount must be non-negative");
    }
    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

money_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock {m_mutex};
    if (!m_is_open) {
        throw std::logic_error("Account not open");
    }
    return m_balance;
}

}  // namespace Bankaccount
