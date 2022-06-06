#include "SavingsAccount.h"
#include <cstring>
#include <iostream>
#pragma warning (disable : 4996)

SavingsAccount::SavingsAccount() :Account()
{
	interestRate = 0;
}

SavingsAccount::SavingsAccount(char* username, char* password, char* iban, char* Id, double amount, char* dateOfCreation,int interestRate)
	:Account(username, password, iban, Id, amount, dateOfCreation)
{
	this->interestRate = interestRate;
}

void SavingsAccount::deposit(const double money)
{
	amount += money;
}

bool SavingsAccount::withdraw(const double money)
{
	return false;
}

void SavingsAccount::display() const
{
	std::cout << "Savings Account, " << "IBAN: " << iban << ", Id: " << Id << ", Amount: " << amount << std::endl;
}

void SavingsAccount::setInterestRate(const int& inputRate) {
	interestRate = inputRate;
}

const int SavingsAccount::getInterestRate() const {
	return interestRate;
}

Account* SavingsAccount::clone() const
{
	return new SavingsAccount(*this);
}