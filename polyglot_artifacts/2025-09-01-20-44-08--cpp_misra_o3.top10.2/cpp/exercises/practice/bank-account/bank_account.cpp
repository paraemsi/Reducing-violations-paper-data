#include "bank_account.h"

#include <stdexcept>

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if(m_is_open) {
        throw std::runtime_error("Account already open");
    } else {
        m_is_open = true;
        m_balance = static_cast<amount_t>(0);
    }
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account not open");
    } else {
        m_is_open = false;
    }
}

void Bankaccount::deposit(amount_t amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    if(amount < static_cast<amount_t>(0)) {
        throw std::runtime_error("Negative deposit");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(amount_t amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    if(amount < static_cast<amount_t>(0)) {
        throw std::runtime_error("Negative withdrawal");
    }
    if(amount > m_balance) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}



amount_t Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_mutex);
    if(!m_is_open) {
        throw std::runtime_error("Account not open");
    }
    return m_balance;
}

}  // namespace Bankaccount
