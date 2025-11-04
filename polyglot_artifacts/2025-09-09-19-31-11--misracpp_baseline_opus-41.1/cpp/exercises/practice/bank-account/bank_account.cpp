#include "bank_account.h"
#include <stdexcept>

namespace Bankaccount {

Bankaccount::Bankaccount() : account_balance(0), is_open(false) {}

Bankaccount::~Bankaccount() {}

void Bankaccount::open() {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (is_open) {
        throw std::runtime_error("Account already open");
    }
    is_open = true;
    account_balance = 0;
}

void Bankaccount::close() {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (!is_open) {
        throw std::runtime_error("Account not open");
    }
    is_open = false;
}

int Bankaccount::balance() const {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (!is_open) {
        throw std::runtime_error("Account not open");
    }
    return account_balance;
}

void Bankaccount::deposit(int amount) {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (!is_open) {
        throw std::runtime_error("Account not open");
    }
    if (amount <= 0) {
        throw std::runtime_error("Deposit amount must be positive");
    }
    account_balance += amount;
}

void Bankaccount::withdraw(int amount) {
    std::lock_guard<std::mutex> lock(account_mutex);
    if (!is_open) {
        throw std::runtime_error("Account not open");
    }
    if (amount <= 0) {
        throw std::runtime_error("Withdrawal amount must be positive");
    }
    if (amount > account_balance) {
        throw std::runtime_error("Insufficient funds");
    }
    account_balance -= amount;
}

}  // namespace Bankaccount
