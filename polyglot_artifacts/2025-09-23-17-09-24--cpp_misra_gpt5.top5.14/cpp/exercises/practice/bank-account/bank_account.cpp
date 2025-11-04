#include "bank_account.h"

#include <limits>
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_open(false),
      m_balance(static_cast<std::int64_t>(0)) {}

void Bankaccount::open() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((m_open)) {
    throw std::runtime_error("Account already open");
  } else {
    m_open = true;
    m_balance = static_cast<std::int64_t>(0);
  }
}

void Bankaccount::close() {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((!m_open)) {
    throw std::runtime_error("Account already closed");
  } else {
    m_open = false;
  }
}

void Bankaccount::deposit(std::int64_t amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((!m_open)) {
    throw std::runtime_error("Account is not open");
  }
  if ((amount < static_cast<std::int64_t>(0))) {
    throw std::runtime_error("Deposit amount must be non-negative");
  }
  if ((amount > (std::numeric_limits<std::int64_t>::max() - m_balance))) {
    throw std::overflow_error("Deposit would overflow balance");
  }
  m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(std::int64_t amount) {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((!m_open)) {
    throw std::runtime_error("Account is not open");
  }
  if ((amount < static_cast<std::int64_t>(0))) {
    throw std::runtime_error("Withdrawal amount must be non-negative");
  }
  if ((m_balance < amount)) {
    throw std::runtime_error("Insufficient funds");
  }
  m_balance = (m_balance - amount);
}

std::int64_t Bankaccount::balance() const {
  std::lock_guard<std::mutex> lock(m_mutex);
  if ((!m_open)) {
    throw std::runtime_error("Account is not open");
  } else {
    return m_balance;
  }
}

}  // namespace Bankaccount
