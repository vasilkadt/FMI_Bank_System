#pragma once
#include "Account.h"

class NormalAccount :public Account
{
public:
	NormalAccount();
	NormalAccount(char* username, char* password, char* iban, char* Id, double amount, char* dateOfCreation);

	void deposit(const double money) override;
	bool withdraw(const double money) override;
	void display() const override;

	Account* clone() const override;
};