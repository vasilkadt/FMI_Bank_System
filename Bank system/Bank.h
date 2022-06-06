#pragma once
#include <fstream>
#include "Customer.h"
#include "Account.h"
#include "NormalAccount.h"
#include "SavingsAccount.h"
#include "PrivilegeAccount.h"
#include "Vector.h"

const int MAX_CUSTOMERS = 30;
const int MAX_ACCOUNTS = 30;
const int BUFFER_LINE_SIZE = 1024;

class Bank
{
private:
	char* name;
	char* address;
	Vector<Customer> customers;
	Vector<Account*> accounts;
	int bankOverdraft;
	int bankInterestRate;
	std::ofstream file;

public:
	Bank();
	Bank(char* inputName, char* inputAddress, int inputOverdraft, int inputInterestRate);
	Bank(const Bank& other);
	Bank& operator=(const Bank& other);
	~Bank();

	void menu() const;
	void addCustomer(const Customer& customerToAdd);
	void deleteCustomer(const char* idToDelete);
	void addAccount(const Account& accountToAdd);
	void deleteAccount(const char* ibanToDelete);
	void listCustomers() const;
	void listAccounts() const;
	void listCustomerAccount(const char* customerId) const;
	void withdrawFromAccount(const char* accountId,const double money);
	void depositToAccount(const char* accountId, const double money);
	void exportLog(const char* transaction);
	void transfer(double amountToTransfer, const char* fromIban, const char* toIban);
	void display() const;

	int getInterestRate() const;
	int getOverdraft() const;
private:
	void copy(const Bank& other);
	void free();
};