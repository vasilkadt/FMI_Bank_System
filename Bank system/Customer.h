#pragma once
#include "Account.h"
#include "Vector.h"

const int MAX_ACCOUNT_SIZE = 20;

class Customer
{
private:
	char* id;
	char* name;
	char* address;

public:
	Customer();
	Customer(char* id, char* name, char* address);
	Customer(const Customer& other);
	Customer& operator=(const Customer& other);
	~Customer();

	void setId(const char* id);
	void setName(const char* name);
	void setAddress(const char* address);

	const char* getId() const;
	const char* getName() const;
	const char* getAddress() const;

private:
	void copy(const Customer& other);
	void free();
};
