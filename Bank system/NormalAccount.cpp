#include "NormalAccount.h"
#include <cstring>
#include <iostream>
#pragma warning (disable : 4996)

NormalAccount::NormalAccount() :Account() {}

NormalAccount::NormalAccount(char* username, char* password, char* iban, char* Id, double amount, char* dateOfCreation)
	:Account(username, password, iban, Id, amount, dateOfCreation) {}

void NormalAccount::deposit(const double money)
{
	amount += money;
}

bool NormalAccount::withdraw(const double money)
{
	if (amount < money)
	{
		return false;
	}
	else
	{
		amount -= money;
		return true;
	}
}

void NormalAccount::display() const
{
	std::cout << "Normal Account, " << "IBAN: " << iban << ", Id: " << Id << ", Amount: " << amount << std::endl;
}

Account* NormalAccount::clone() const
{
	return new NormalAccount(*this);
}