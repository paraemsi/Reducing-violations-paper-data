#include "bank_account.h"
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept : m_mutex(), m_is_open(false), m_balance(amount_type{0}) {}

void Bankaccount::open()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((m_is_open) == true)
  {
    throw std::runtime_error("account already open");
  }
  m_balance = amount_type{0};
  m_is_open = true;
}

void Bankaccount::close()
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((m_is_open) == false)
  {
    throw std::runtime_error("account already closed");
  }
  m_is_open = false;
}

void Bankaccount::deposit(amount_type amount)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((m_is_open) == false)
  {
    throw std::runtime_error("account not open");
  }
  if ((amount) < amount_type{0})
  {
    throw std::runtime_error("negative deposit");
  }
  m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(amount_type amount)
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((m_is_open) == false)
  {
    throw std::runtime_error("account not open");
  }
  if ((amount) < amount_type{0})
  {
    throw std::runtime_error("negative withdrawal");
  }
  if ((m_balance) < amount)
  {
    throw std::runtime_error("insufficient funds");
  }
  m_balance = (m_balance - amount);
}

Bankaccount::amount_type Bankaccount::balance() const
{
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((m_is_open) == false)
  {
    throw std::runtime_error("account not open");
  }
  return m_balance;
}

}  // namespace Bankaccount
