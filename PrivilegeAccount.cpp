#include "PrivilegeAccount.h"
#include <cstring>
#include <iostream>
#pragma warning (disable : 4996)

PrivilegeAccount::PrivilegeAccount() :Account()
{
	overdraft = 0;
}

PrivilegeAccount::PrivilegeAccount(char* username, char* password, char* iban, char* Id, double amount, char* dateOfCreation, int overdraft)
	: Account(username, password, iban, Id, amount, dateOfCreation)
{
	this->overdraft = overdraft;
}

void PrivilegeAccount::setOverdraft(const int inputOverdraft) {
	this->overdraft = inputOverdraft;
}

int PrivilegeAccount::getOverdraft() const {
	return this->overdraft;
}

void PrivilegeAccount::deposit(const double money)
{
	amount += money;
}

bool PrivilegeAccount::withdraw(const double money)
{
	if (amount + overdraft < money)
	{
		return false;
	}
	else
	{
		amount -= money;
		return true;
	}
}

void PrivilegeAccount::display() const
{
	std::cout << "Privilege Account, " << "IBAN: " << iban << ", Id: " << Id << ", Amount: " << amount << std::endl;
}

Account* PrivilegeAccount::clone() const
{
	return new PrivilegeAccount(*this);
}