#pragma once
#include "Account.h"

class PrivilegeAccount :public Account
{
private:
	int overdraft;

public:
	PrivilegeAccount();
	PrivilegeAccount(char* username, char* password, char* iban, char* Id, double amount, char* dateOfCreation, int overdraft);

	void deposit(const double money) override;
	bool withdraw(const double money) override;
	void display() const override;

	void setOverdraft(const int inputOverdraft);
	int getOverdraft() const;

	Account* clone() const override;
};