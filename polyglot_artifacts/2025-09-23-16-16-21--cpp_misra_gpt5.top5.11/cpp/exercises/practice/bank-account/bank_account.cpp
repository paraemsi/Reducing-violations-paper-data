#include "bank_account.h"

#include <limits>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_balance(static_cast<amount_type>(0)),
      m_open(false)
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open) == true)
    {
        throw std::runtime_error("account already open");
    }
    m_balance = static_cast<amount_type>(0);
    m_open = true;
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open) == false)
    {
        throw std::runtime_error("account not open");
    }
    m_open = false;
}

void Bankaccount::deposit(amount_type amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open) == false)
    {
        throw std::runtime_error("account not open");
    }
    if ((amount <= static_cast<amount_type>(0)) == true)
    {
        throw std::runtime_error("deposit amount must be positive");
    }
    amount_type const max_allowed = (std::numeric_limits<amount_type>::max)();
    if ((m_balance > (max_allowed - amount)) == true)
    {
        throw std::runtime_error("deposit would overflow");
    }
    m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(amount_type amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open) == false)
    {
        throw std::runtime_error("account not open");
    }
    if ((amount <= static_cast<amount_type>(0)) == true)
    {
        throw std::runtime_error("withdraw amount must be positive");
    }
    if ((m_balance < amount) == true)
    {
        throw std::runtime_error("insufficient funds");
    }
    m_balance = (m_balance - amount);
}

Bankaccount::amount_type Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open) == false)
    {
        throw std::runtime_error("account not open");
    }
    return m_balance;
}

}  // namespace Bankaccount
