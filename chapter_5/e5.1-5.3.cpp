#include <cstdio>
#include <stdexcept>

struct AccountDatabase {
    virtual ~AccountDatabase() = default;
    virtual size_t add_account(void) = 0;
    virtual double get_balance(size_t id) const = 0;
    virtual void set_balance(size_t id, double balance) = 0;
};

struct InMemoryAccountDatabase : AccountDatabase {
    private:
        double *accounts;
        size_t max_accounts;
        size_t next_id;
    public:
        // Constructor
        InMemoryAccountDatabase(const size_t max_accounts)
                : max_accounts{ max_accounts },
                  next_id { 0 } {
            accounts = new double[max_accounts];
        }
        // Destructor
        ~InMemoryAccountDatabase() override {
            if (accounts) {
                delete[] accounts;
            }
        }
        // Copy constructor
        InMemoryAccountDatabase(const InMemoryAccountDatabase& other)
                : max_accounts{ other.max_accounts },
                  next_id{ other.next_id } {
            accounts = new double[max_accounts];
            for (size_t i = 0; i < next_id; i++) {
                accounts[i] = other.accounts[i];
            }
        }
        // Move constructor
        InMemoryAccountDatabase(InMemoryAccountDatabase&& other) noexcept
                : max_accounts{ other.max_accounts },
                  next_id{ other.next_id } {
            delete[] accounts;
            accounts = other.accounts;
            other.accounts = nullptr;
            other.max_accounts = 0;
            other.next_id = 0;
        }
        // Copy-assign
        InMemoryAccountDatabase&
        operator=(const InMemoryAccountDatabase& other) {
            if (this == &other) { return *this; }
            max_accounts = other.max_accounts;
            next_id = other.next_id;
            delete[] accounts;
            accounts = new double[max_accounts];
            for (size_t i = 0; i < next_id; i++) {
                accounts[i] = other.accounts[i];
            }
            return *this;
        }
        // Move-assign
        InMemoryAccountDatabase&
        operator=(InMemoryAccountDatabase&& other)
        noexcept {
            if (this == &other) { return *this; }
            delete[] accounts;
            accounts = other.accounts;
            max_accounts = other.max_accounts;
            next_id = other.next_id;
            other.accounts = nullptr;
            other.max_accounts = 0;
            other.next_id = 0;
            return *this;
        }
        size_t add_account(void) override {
            if (next_id < max_accounts) {
                const long id = next_id;
                next_id++;
                accounts[id] = 0.0;
                return id;
            } else {
                return -1;
            }
        }
        double get_balance(const size_t id) const override {
            if (id < next_id) {
                return accounts[id];
            } else {
                throw std::runtime_error{ "invalid account ID" };
            }
        }
        void set_balance(const size_t id, const double balance) override {
            if (id < next_id) {
                accounts[id] = balance;
            } else {
                throw std::runtime_error{ "invalid account ID" };
            }
        }
};

struct Logger {
    virtual ~Logger() = default;
    virtual void log_transfer(size_t from, size_t to, double amount) = 0;
};

struct ConsoleLogger : Logger {
    void log_transfer(size_t from, size_t to, double amount) override {
        printf("[cons] %zu -> %zu: %f\n", from, to, amount);
    }
};

struct FileLogger : Logger {
    void log_transfer(size_t from, size_t to, double amount) override {
        printf("[file] %zu,%zu,%f\n", from, to, amount);
    }
};

struct Bank {
private:
    Logger* logger;
public:
    InMemoryAccountDatabase& db;

    Bank(InMemoryAccountDatabase& db) : db{ db } {}
    void set_logger(Logger* new_logger) {
        logger = new_logger;
    }
    void make_transfer(size_t from, size_t to, double amount) {
        if (amount < 0.0) {
            throw std::runtime_error{ "transfer amount must be nonnegative" };
        }
        double from_balance = db.get_balance(from);
        double to_balance = db.get_balance(to);
        if (amount <= from_balance) {
            db.set_balance(from, from_balance - amount);
            db.set_balance(to, to_balance + amount);
            if(logger) {
                logger->log_transfer(from, to, amount);
            }
        } else {
            throw std::runtime_error{ "insufficient funds" };
        }
    }
};

int main() {
    ConsoleLogger console_logger;
    FileLogger file_logger;
    InMemoryAccountDatabase db{ 16 };
    Bank bank{ db };
    size_t id0 = bank.db.add_account();
    size_t id1 = bank.db.add_account();
    bank.db.set_balance(id0, 1024.0);
    bank.db.set_balance(id1, 5.12);
    bank.set_logger(&console_logger);
    bank.make_transfer(id0, id1, 49.95);
    bank.set_logger(&file_logger);
    bank.make_transfer(id1, id0, 20.00);
}
