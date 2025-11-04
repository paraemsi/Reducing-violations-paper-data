#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : m_balance(0), m_is_open(false) {
}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (m_is_open) {
        throw std::runtime_error("Account is already open");
    }
    m_is_open = true;
    // Don't reset balance when reopening? The instructions aren't clear
    // Let's set it to 0 as per initial implementation
    m_balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account is not open");
    }
    m_is_open = false;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    if ((amount <= 0)) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if ((amount > m_balance)) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!m_is_open) {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

}  // namespace Bankaccount
