#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() noexcept
    : m_mutex(),
      m_open(false),
      m_balance(static_cast<int64_t>(0)) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == true)) {
        throw std::runtime_error("account already open");
    } else {
        m_open = true;
        m_balance = static_cast<int64_t>(0);
    }
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == false)) {
        throw std::runtime_error("account already closed");
    } else {
        m_open = false;
    }
}

void Bankaccount::deposit(int64_t amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == false)) {
        throw std::runtime_error("deposit on closed account");
    }

    constexpr int64_t zero = static_cast<int64_t>(0);
    if ((amount < zero)) {
        throw std::runtime_error("negative deposit not allowed");
    }

    m_balance = (m_balance + amount);
}

void Bankaccount::withdraw(int64_t amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == false)) {
        throw std::runtime_error("withdrawal on closed account");
    }

    constexpr int64_t zero = static_cast<int64_t>(0);
    if ((amount < zero)) {
        throw std::runtime_error("negative withdrawal not allowed");
    }

    if ((m_balance < amount)) {
        throw std::runtime_error("insufficient funds");
    } else {
        m_balance = (m_balance - amount);
    }
}

int64_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if ((m_open == false)) {
        throw std::runtime_error("balance requested from closed account");
    } else {
        return m_balance;
    }
}

}  // namespace Bankaccount
