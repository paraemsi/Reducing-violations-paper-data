#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_is_open(false),
      m_balance(static_cast<Money>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_is_open) {
        m_balance = static_cast<Money>(0);
        m_is_open = true;
    } else {
        throw std::runtime_error("Account already open");
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_is_open) {
        m_is_open = false;
    } else {
        throw std::runtime_error("Account already closed");
    }
}

void Bankaccount::deposit(Money amount)
{
    if(amount < static_cast<Money>(0)) {
        throw std::runtime_error("Deposit amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_is_open) {
        m_balance += amount;
    } else {
        throw std::runtime_error("Account is closed");
    }
}

void Bankaccount::withdraw(Money amount)
{
    if(amount < static_cast<Money>(0)) {
        throw std::runtime_error("Withdraw amount must be non-negative");
    }

    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    if(m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

Bankaccount::Money Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
