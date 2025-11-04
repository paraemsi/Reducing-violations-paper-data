#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_open(false),
      m_balance(static_cast<money_t>(0))
{
}

void Bankaccount::open()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == true)) {
        throw std::runtime_error("account already open");
    } else {
        m_open = true;
        m_balance = static_cast<money_t>(0);
    }
}

void Bankaccount::close()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == false)) {
        throw std::runtime_error("account already closed");
    } else {
        m_open = false;
    }
}

void Bankaccount::deposit(money_t amount)
{
    if ((amount < static_cast<money_t>(0))) {
        throw std::runtime_error("negative deposit");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == false)) {
        throw std::runtime_error("account closed");
    } else {
        m_balance = (m_balance + amount);
    }
}

void Bankaccount::withdraw(money_t amount)
{
    if ((amount < static_cast<money_t>(0))) {
        throw std::runtime_error("negative withdrawal");
    }
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == false)) {
        throw std::runtime_error("account closed");
    } else if ((m_balance < amount)) {
        throw std::runtime_error("insufficient funds");
    } else {
        m_balance = (m_balance - amount);
    }
}

money_t Bankaccount::balance() const
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == false)) {
        throw std::runtime_error("account closed");
    } else {
        return m_balance;
    }
}

}  // namespace Bankaccount
