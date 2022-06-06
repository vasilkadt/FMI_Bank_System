#pragma once
#include "Account.h"

class SavingsAccount :public Account
{
private:
	int interestRate;

public:
	SavingsAccount();
	SavingsAccount(char* username, char* password, char* iban, char* Id, double amount, char* dateOfCreation,int interestRate);

	void deposit(const double money) override;
	bool withdraw(const double money) override;
	void display() const override;

	void setInterestRate(const int& inputRate);
	const int getInterestRate() const;

	Account* clone() const override;
};