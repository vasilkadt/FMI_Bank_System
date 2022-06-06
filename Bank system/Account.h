#pragma once

class Account
{
protected:
	char* username;
	char* password;
	char* iban;
	char* Id;
	double amount;
	char* dateOfCreation;

public:
	Account();
	Account(char* username, char* password);
	Account(char* username, char* password, char* iban, char* Id, double amount, char* dateOfCreation);
	Account(const Account& other);
	Account& operator=(const Account& other);
	virtual ~Account();

	void setUsername(const char* username);
	void setPassword(const char* password);

	virtual void deposit(const double money) = 0;
	virtual bool withdraw(const double money) = 0;
	virtual void display() const = 0;
	double getBalance() const;

	const char* getId() const;
	const char* getIban() const;
	virtual Account* clone() const = 0;

private:
	void copy(const Account& other);
	void free();
};