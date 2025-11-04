#include "bank_account.h"

namespace Bankaccount {

Bankaccount::Bankaccount()
    : m_balance(0), m_open(false)
{
}

Bankaccount::~Bankaccount()
{
    // No dynamic resources to release
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_open = true;
    m_balance = static_cast<money_t>(0);
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_open = false;
}

bool Bankaccount::deposit(money_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((!m_open) || (amount < static_cast<money_t>(0))) {
        return false;
    }
    m_balance = (m_balance + amount);
    return true;
}

bool Bankaccount::withdraw(money_t amount)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((!m_open) || (amount < static_cast<money_t>(0)) || (m_balance < amount)) {
        return false;
    }
    m_balance = (m_balance - amount);
    return true;
}

bool Bankaccount::get_balance(money_t& out_balance)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        return false;
    }
    out_balance = m_balance;
    return true;
}

// Provide a public balance() method for test compatibility
money_t Bankaccount::balance()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

} // namespace Bankaccount
