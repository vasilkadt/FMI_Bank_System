#include "Customer.h"
#include <cstring>
#pragma warning (disable : 4996)

Customer::Customer()
{
	id = nullptr;
	name = nullptr;
	address = nullptr;
}

Customer::Customer(char* id, char* name, char* address)
{
	setId(id);
	setName(name);
	setAddress(address);
}

Customer::Customer(const Customer& other)
{
	copy(other);
}

Customer& Customer::operator=(const Customer& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

Customer::~Customer()
{
	free();
}

void Customer::setId(const char* id)
{
	delete[] this->id;
	this->id = new char[strlen(id) + 1];
	strcpy(this->id, id);
}

void Customer::setName(const char* name)
{
	delete[] this->name;
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}

void Customer::setAddress(const char* address)
{
	delete[] this->address;
	this->address = new char[strlen(address) + 1];
	strcpy(this->address, address);
}

const char* Customer::getId() const
{
	return id;
}

const char* Customer::getName() const
{
	return name;
}

const char* Customer::getAddress() const
{
	return address;
}

void Customer::copy(const Customer& other)
{
	id = new char[strlen(other.id) + 1];
	strcpy(id, other.id);
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	address = new char[strlen(other.address) + 1];
	strcpy(address, other.address);
}

void Customer::free()
{
	delete[] id;
	delete[] name;
	delete[] address;
}