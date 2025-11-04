#include "bank_account.h"

namespace Bankaccount {

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(m_);
    if (open_) {
        throw std::runtime_error("account already open");
    }
    open_ = true;
    balance_ = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(m_);
    if (!open_) {
        throw std::runtime_error("account not open");
    }
    open_ = false;
    balance_ = 0;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(m_);
    if (!open_) {
        throw std::runtime_error("account not open");
    }
    if (amount < 0) {
        throw std::runtime_error("negative deposit");
    }
    balance_ += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(m_);
    if (!open_) {
        throw std::runtime_error("account not open");
    }
    if (amount < 0) {
        throw std::runtime_error("negative withdrawal");
    }
    if (balance_ < amount) {
        throw std::runtime_error("insufficient funds");
    }
    balance_ -= amount;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(m_);
    if (!open_) {
        throw std::runtime_error("account not open");
    }
    return balance_;
}

}  // namespace Bankaccount
