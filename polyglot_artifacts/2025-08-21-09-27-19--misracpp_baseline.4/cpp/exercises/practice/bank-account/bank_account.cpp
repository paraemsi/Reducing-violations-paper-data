#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount()
    : m_balance(0), m_open(false) {}

Bankaccount::~Bankaccount() {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (m_open) {
        throw std::runtime_error("Account already open");
    }
    m_balance = 0;
    m_open = true;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account not open");
    }
    m_open = false;
}

int Bankaccount::balance() {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    }
    return m_balance;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Cannot deposit negative amount");
    }
    m_balance += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_open) {
        throw std::runtime_error("Account is closed");
    }
    if (amount < 0) {
        throw std::runtime_error("Cannot withdraw negative amount");
    }
    if (m_balance < amount) {
        throw std::runtime_error("Insufficient funds");
    }
    m_balance -= amount;
}

} // namespace Bankaccount
