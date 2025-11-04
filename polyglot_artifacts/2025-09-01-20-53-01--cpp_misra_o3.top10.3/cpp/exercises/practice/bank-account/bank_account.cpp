#include "bank_account.h"
#include <stdexcept>


namespace Bankaccount {

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lk(m_mutex);
    if(m_is_open) {
        throw std::runtime_error("Account already open");
    } else {
        m_balance = static_cast<std::int64_t>(0);
        m_is_open = true;
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lk(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account not open");
    } else {
        m_is_open = false;
        m_balance = static_cast<std::int64_t>(0);
    }
}

void Bankaccount::deposit(std::int64_t amount)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    if(amount <= static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(std::int64_t amount)
{
    std::lock_guard<std::mutex> lk(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    if(amount <= static_cast<std::int64_t>(0)) {
        throw std::runtime_error("Withdraw amount must be positive");
    }
    if(m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

std::int64_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lk(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    return m_balance;
}

}  // namespace Bankaccount

