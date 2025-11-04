#include "bank_account.h"
#include <stdexcept>
#include <cstdint>
#include <mutex>

namespace Bankaccount {

// Internal implementation using fixed-width types
class BankaccountImpl {
public:
    using InternalAmountType = std::int64_t;
    
    BankaccountImpl() : balance(0), is_open(false) {}
    
    void open() {
        std::lock_guard<std::mutex> lock(mutex);
        if (is_open) {
            throw std::runtime_error("Account is already open");
        }
        is_open = true;
        balance = 0;
    }
    
    void deposit(InternalAmountType amount) {
        std::lock_guard<std::mutex> lock(mutex);
        if (!is_open) {
            throw std::runtime_error("Account is closed");
        }
        if ((amount <= 0)) {
            throw std::invalid_argument("Deposit amount must be positive");
        }
        balance += amount;
    }
    
    void withdraw(InternalAmountType amount) {
        std::lock_guard<std::mutex> lock(mutex);
        if (!is_open) {
            throw std::runtime_error("Account is closed");
        }
        if ((amount <= 0)) {
            throw std::invalid_argument("Withdrawal amount must be positive");
        }
        if ((amount > balance)) {
            throw std::runtime_error("Insufficient funds");
        }
        balance -= amount;
    }
    
    InternalAmountType get_balance() const {
        std::lock_guard<std::mutex> lock(mutex);
        if (!is_open) {
            throw std::runtime_error("Account is closed");
        }
        return balance;
    }
    
    void close() {
        std::lock_guard<std::mutex> lock(mutex);
        if (!is_open) {
            throw std::runtime_error("Account is not open");
        }
        is_open = false;
    }
    
private:
    mutable std::mutex mutex;
    InternalAmountType balance;
    bool is_open;
};

// Bankaccount wrapper implementation
Bankaccount::Bankaccount() : impl(new BankaccountImpl()) {}
Bankaccount::~Bankaccount() { delete impl; }

void Bankaccount::open() { impl->open(); }
void Bankaccount::deposit(int64_t amount) { impl->deposit(amount); }
void Bankaccount::withdraw(int64_t amount) { impl->withdraw(amount); }
int64_t Bankaccount::balance() const { return impl->get_balance(); }
void Bankaccount::close() { impl->close(); }

}  // namespace Bankaccount
