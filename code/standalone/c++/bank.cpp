#include <iomanip>
#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class Transaction {
public:
  std::string type;
  double amount;
  double balanceAfterTransaction;

  Transaction(const std::string &type, double amount, double balance)
      : type(type), amount(amount), balanceAfterTransaction(balance) {}
};

class BankAccount {
private:
  std::string accountHolder;
  double balance;
  std::vector<Transaction> transactionHistory;

public:
  BankAccount(const std::string &name, double initialBalance)
      : accountHolder(name), balance(initialBalance) {
    transactionHistory.emplace_back("Initial Deposit", initialBalance,
                                    initialBalance);
  }

  // 存款
  void deposit(double amount) {
    if (amount > 0) {
      balance += amount;
      transactionHistory.emplace_back("Deposit", amount, balance);
      std::cout << "Deposit successful. New balance: " << balance << std::endl;
    } else {
      std::cout << "Invalid deposit amount!" << std::endl;
    }
  }

  // 取款
  void withdraw(double amount) {
    if (amount > 0 && amount <= balance) {
      balance -= amount;
      transactionHistory.emplace_back("Withdraw", amount, balance);
      std::cout << "Withdrawal successful. New balance: " << balance
                << std::endl;
    } else if (amount > balance) {
      std::cout << "Insufficient balance!" << std::endl;
    } else {
      std::cout << "Invalid withdrawal amount!" << std::endl;
    }
  }

  // 查询余额
  double getBalance() const { return balance; }

  // 显示交易历史
  void displayTransactionHistory() const {
    std::cout << "Transaction History for " << accountHolder << ":\n";
    std::cout << std::left << std::setw(15) << "Type" << std::setw(10)
              << "Amount" << std::setw(20) << "Balance After\n";

    for (const auto &transaction : transactionHistory) {
      std::cout << std::left << std::setw(15) << transaction.type
                << std::setw(10) << transaction.amount << std::setw(20)
                << transaction.balanceAfterTransaction << std::endl;
    }
  }
};

class Bank {
private:
  std::unordered_map<std::string, std::shared_ptr<BankAccount>> accounts;

public:
  void createAccount(const std::string &name, double initialDeposit) {
    if (accounts.find(name) == accounts.end()) {
      accounts[name] = std::make_shared<BankAccount>(name, initialDeposit);
      std::cout << "Account for " << name << " created successfully.\n";
    } else {
      std::cout << "Account with this name already exists.\n";
    }
  }

  void deposit(const std::string &name, double amount) {
    auto account = findAccount(name);
    if (account != nullptr) {
      account->deposit(amount);
    }
  }

  // 取款操作
  void withdraw(const std::string &name, double amount) {
    auto account = findAccount(name);
    if (account != nullptr) {
      account->withdraw(amount);
    }
  }

  // 查询余额
  void checkBalance(const std::string &name) const {
    auto account = findAccount(name);
    if (account != nullptr) {
      std::cout << "Current balance for " << name << ": "
                << account->getBalance() << std::endl;
    }
  }

  // 显示交易历史
  void displayTransactionHistory(const std::string &name) const {
    auto account = findAccount(name);
    if (account != nullptr) {
      account->displayTransactionHistory();
    }
  }

private:
  std::shared_ptr<BankAccount> findAccount(const std::string &name) const {
    auto it = accounts.find(name);
    if (it != accounts.end()) {
      return it->second;
    } else {
      std::cout << "Account not found!\n";
      return nullptr;
    }
  }
};

// 菜单函数
void displayMenu() {
  std::cout << "\n--- Bank System Menu ---\n";
  std::cout << "1. Create a new account\n";
  std::cout << "2. Deposit money\n";
  std::cout << "3. Withdraw money\n";
  std::cout << "4. Check balance\n";
  std::cout << "5. View transaction history\n";
  std::cout << "6. Exit\n";
  std::cout << "Choose an option: ";
}

int main() {
  Bank bank;
  int choice;
  std::string name;
  double amount;

  do {
    displayMenu();
    std::cin >> choice;

    switch (choice) {
    case 1:
      std::cout << "Enter account holder's name: ";
      std::cin >> name;
      std::cout << "Enter initial deposit: ";
      std::cin >> amount;
      bank.createAccount(name, amount);
      break;

    case 2:
      std::cout << "Enter account holder's name: ";
      std::cin >> name;
      std::cout << "Enter deposit amount: ";
      std::cin >> amount;
      bank.deposit(name, amount);
      break;

    case 3:
      std::cout << "Enter account holder's name: ";
      std::cin >> name;
      std::cout << "Enter withdrawal amount: ";
      std::cin >> amount;
      bank.withdraw(name, amount);
      break;

    case 4:
      std::cout << "Enter account holder's name: ";
      std::cin >> name;
      bank.checkBalance(name);
      break;

    case 5:
      std::cout << "Enter account holder's name: ";
      std::cin >> name;
      bank.displayTransactionHistory(name);
      break;

    case 6:
      std::cout << "Exiting system. Goodbye!\n";
      break;

    default:
      std::cout << "Invalid choice. Please try again.\n";
      break;
    }
  } while (choice != 6);

  return 0;
}