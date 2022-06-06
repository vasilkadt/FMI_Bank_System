#include "Account.h"
#include <cstring>
#include <iostream>
#pragma warning (disable : 4996)

Account::Account()
{
	username = nullptr;
	password = nullptr;
	iban = nullptr;
	Id = nullptr;
	amount = 0;
	dateOfCreation = 0;
}

Account::Account(char* username, char* password)
{
	setUsername(username);
	setPassword(password);
}

Account::Account(char* username, char* password, char* iban, char* Id, double amount, char* dateOfCreation)
{
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
	this->iban = new char[strlen(iban) + 1];
	strcpy(this->iban, iban);
	this->Id = new char[strlen(Id) + 1];
	strcpy(this->Id, Id);
	this->amount = amount;
	this->dateOfCreation = new char[strlen(dateOfCreation) + 1];
	strcpy(this->dateOfCreation, dateOfCreation);
}

Account::Account(const Account& other)
{
	copy(other);
}

Account& Account::operator=(const Account& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

Account::~Account()
{
	free();
}

void Account::setUsername(const char* username)
{
	delete[] this->username;
	this->username = new char[strlen(username) + 1];
	strcpy(this->username, username);
}

void Account::setPassword(const char* password)
{
	delete[] this->password;
	this->password = new char[strlen(password) + 1];
	strcpy(this->password, password);
}

double Account::getBalance() const
{
	return amount;
}

const char* Account::getId() const
{
	return Id;
}

const char* Account::getIban() const
{
	return iban;
}

void Account::copy(const Account& other)
{
	username = new char[strlen(other.username) + 1];
	strcpy(username, other.username);
	password = new char[strlen(other.password) + 1];
	strcpy(password, other.password);
	iban = new char[strlen(other.iban) + 1];
	strcpy(iban, other.iban);
	Id = new char[strlen(other.Id) + 1];
	strcpy(Id, other.Id);
	amount = other.amount;
	dateOfCreation = new char[strlen(other.dateOfCreation) + 1];
	strcpy(dateOfCreation, other.dateOfCreation);
}

void Account::free()
{
	delete[] username;
	delete[] password;
	delete[] iban;
	delete[] Id;
	delete[] dateOfCreation;
}