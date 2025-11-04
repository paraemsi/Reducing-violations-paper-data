#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : balance(0), is_open(false) {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(mtx);
    if (is_open) {
        throw std::runtime_error("Account already open");
    }
    is_open = true;
    balance = 0;
}

void Bankaccount::deposit(AccountValue amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    balance = (balance + amount);
}

void Bankaccount::withdraw(AccountValue amount) {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account closed");
    }
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if (amount > balance) {
        throw std::runtime_error("Insufficient funds");
    }
    balance = (balance - amount);
}

AccountValue Bankaccount::get_balance() const {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account closed");
    }
    return balance;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(mtx);
    if (!is_open) {
        throw std::runtime_error("Account not open");
    }
    is_open = false;
}

}  // namespace Bankaccount
