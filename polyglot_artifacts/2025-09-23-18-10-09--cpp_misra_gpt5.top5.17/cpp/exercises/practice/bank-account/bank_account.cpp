#include "bank_account.h"

#include <limits>
#include <mutex>
#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((m_open)) {
    throw std::runtime_error("Account already open");
  }
  m_balance = 0;
  m_open = true;
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((!m_open)) {
    throw std::runtime_error("Account not open");
  }
  m_open = false;
}

void Bankaccount::deposit(std::int64_t amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((!m_open)) {
    throw std::runtime_error("Account not open");
  }
  if ((amount < static_cast<std::int64_t>(0))) {
    throw std::runtime_error("Negative deposit");
  }
  if ((amount > (std::numeric_limits<std::int64_t>::max() - m_balance))) {
    throw std::overflow_error("Balance overflow");
  }
  m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(std::int64_t amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((!m_open)) {
    throw std::runtime_error("Account not open");
  }
  if ((amount < static_cast<std::int64_t>(0))) {
    throw std::runtime_error("Negative withdrawal");
  }
  if ((m_balance < amount)) {
    throw std::runtime_error("Insufficient funds");
  }
  m_balance = (m_balance - amount);
}

std::int64_t Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((!m_open)) {
    throw std::runtime_error("Account not open");
  }
  return (m_balance);
}

}  // namespace Bankaccount
