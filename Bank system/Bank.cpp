#include "Bank.h"
#include <cstring>
#include <iostream>
#pragma warning (disable : 4996)

Bank::Bank()
{
	name = nullptr;
	address = nullptr;
	customers = Vector<Customer>();
	accounts = Vector<Account*>();
	bankInterestRate = 0;
	bankOverdraft = 0;
	std::ofstream file("transaction.txt", std::ofstream::app);
}

Bank::Bank(char* inputName, char* inputAddress, int inputOverdraft, int inputInterestRate) {
	this->name = new char[strlen(inputName) + 1];
	strcpy(this->name, inputName);
	this->address = new char[strlen(inputAddress) + 1];
	strcpy(this->address, inputAddress);
	bankInterestRate = inputInterestRate;
	bankOverdraft = inputOverdraft;
	customers = Vector<Customer>();
	accounts = Vector<Account*>();
	std::ofstream file("transaction.txt", std::ofstream::app);
}

Bank::Bank(const Bank& other)
{
	copy(other);
}

Bank& Bank::operator=(const Bank& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

Bank::~Bank()
{
	free();
}

void Bank::addCustomer(const Customer& customerToAdd)
{
	customers.pushBack(customerToAdd);
	exportLog("Customer added!");
}

int Bank::getInterestRate() const {
	return bankInterestRate;
}

int Bank::getOverdraft() const {
	return bankOverdraft;
}

void Bank::deleteCustomer(const char* idToDelete)
{
	int customerIndex = 0;
	bool customerExists = false;
	for (size_t i = 0; i < customers.getSize(); i++)
	{
		if (strcmp(customers[i].getId(), idToDelete) == 0)
		{
			customerIndex = i;
			customerExists = true;
		}
	}
	if (!customerExists)
	{
		std::cout << "Customer not fount!" << std::endl;
	}
	else
	{
		exportLog("Customer deleted!");
		customers.popAt(customerIndex);
	}
}

void Bank::addAccount(const Account& accountToAdd)
{
	bool validAccount = false;
	for (size_t i = 0; i < customers.getSize(); i++)
	{
		if (strcmp(customers[i].getId(), accountToAdd.getId()) == 0)
		{
			accounts.pushBack(accountToAdd.clone());
			exportLog("Account added!");
			validAccount = true;
		}
	}
	if (!validAccount)
	{
		std::cout << "Invalid account!" << std::endl;
	}
}

void Bank::deleteAccount(const char* ibanToDelete)
{
	int accountIndex = 0;
	bool validAccount = false;
	for (size_t i = 0; i < accounts.getSize(); i++)
	{
		if (strcmp(accounts[i]->getId(), ibanToDelete) == 0)
		{
			accountIndex = i;
			validAccount = true;
		}
	}
	if (validAccount) {
		exportLog("Account deleted!");
		accounts.popAt(accountIndex);
	}
	else
	{
		std::cout << "Invalid account!" << std::endl;
	}
}

void Bank::listCustomers() const
{
	for (size_t i = 0; i < customers.getSize(); i++)
	{
		std::cout << "Name: " << customers[i].getName() << " Id: " << customers[i].getId() << " Address: " << customers[i].getAddress() << std::endl;
	}
	if (customers.getSize() == 0) {
		std::cout << "There are zero customers!" << std::endl;
	}
}

void Bank::listAccounts() const
{
	for (size_t i = 0; i < accounts.getSize(); i++)
	{
		accounts[i]->display();
	}
	if (accounts.getSize() == 0) {
		std::cout << "There are zero bank accounts!" << std::endl;
	}
}

void Bank::listCustomerAccount(const char* customerId) const
{
	bool validId = false;
	bool validUser = false;
	for (size_t i = 0; i < customers.getSize(); i++)
	{
		if (strcmp(customers[i].getId(), customerId) == 0) {
			for (size_t j = 0; j < accounts.getSize(); j++)
			{
				if (strcmp(accounts[j]->getId(), customerId) == 0)
				{
					accounts[j]->display();
					validId = true;
				}
			}
			validUser = true;
		}
	}
	if (!validUser) {
		std::cout << "Invalid user ID!" << std::endl;
	}
	else
	{
		if (!validId) {
			std::cout << "This user has zero accounts!" << std::endl;
		}
	}
}

void Bank::withdrawFromAccount(const char* accountId, const double money) {
	bool validId = false;
	for (size_t i = 0; i < accounts.getSize(); i++)
	{
		if (strcmp(accounts[i]->getId(), accountId) == 0) {
			if (!accounts[i]->withdraw(money)) {
				std::cout << "Can not widthdraw money!" << std::endl;
				return;
			}
			else
			{
				file << "Account with ID: " << accounts[i]->getId() << " widthdrown " <<money<<"!"<< std::endl;
			}
			validId = true;
		}
	}
	if (!validId) {
		std::cout << "Invalid account ID!" << std::endl;
	}
}

void Bank::depositToAccount(const char* accountId, const double money) {
	bool validId = false;
	for (size_t i = 0; i < accounts.getSize(); i++)
	{
		if (strcmp(accounts[i]->getId(), accountId) == 0) {
			accounts[i]->deposit(money);
			file << "Account with ID: " << accounts[i]->getId() << " desposit " << money << "!" << std::endl;
			validId = true;
		}
	}
	if (!validId) {
		std::cout << "Invalid account ID!" << std::endl;
	}
}

void Bank::exportLog(const char* transaction)
{
	std::ofstream file("transaction.txt", std::ofstream::app);

	if (!file.is_open())
	{
		std::cout << "Error opening the file!";
		return;
	}

	file << transaction << std::endl;
}

void Bank::transfer(double amountToTransfer, const  char* fromIban, const char* toIban)
{
	bool isFirstAccountFound = false;
	int firstAccountPossition = 0;
	bool isSecondAccountFound = false;
	int secondAccountPossition = 0;
	for (size_t i = 0; i < accounts.getSize(); i++)
	{
		if (strcmp(accounts[i]->getIban(), fromIban))
		{
			isFirstAccountFound = true;
			firstAccountPossition = i;
		}
	}
	if (!isFirstAccountFound) {
		std::cout << "Invalid first IBAN" << std::endl;
		return;
	}
	else
	{
		for (size_t i = 0; i < accounts.getSize(); i++)
		{
			if (strcmp(accounts[i]->getIban(), toIban) == 0)
			{
				isSecondAccountFound = true;
				secondAccountPossition = i;
			}
		}
	}
	if (!isSecondAccountFound) {
		std::cout << "Invalid second IBAN" << std::endl;
		return;
	}
	if (secondAccountPossition == firstAccountPossition) {
		std::cout << "Can not choose the same IBAN" << std::endl;
		return;
	}
	if (accounts[firstAccountPossition]->withdraw(amountToTransfer))
	{
		accounts[secondAccountPossition]->deposit(amountToTransfer);
		exportLog("Transfer money!\n");
	}
	else std::cout << "Not enough money in this IBAN!";
}

void Bank::display() const
{
	std::cout << "Name: " << name << std::endl;
	std::cout << "Address: " << address << std::endl;
	if (customers.getSize() == 0)
	{
		std::cout << "There are no customers to show!" << std::endl;
	}
	else
	{
		std::cout << "Customers: " << std::endl;
		for (size_t i = 0; i < customers.getSize(); i++)
		{
			std::cout << i + 1 << ". " << customers[i].getName() << std::endl;
		}
	}
	if (accounts.getSize() == 0)
	{
		std::cout << "There are no accounts wo show!" << std::endl;
	}
	else
	{
		std::cout << "Accounts: " << std::endl;
		for (size_t i = 0; i < accounts.getSize(); i++)
		{
			std::cout << i + 1 << ". ";
			accounts[i]->display();
		}
	}
}

void Bank::copy(const Bank& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	address = new char[strlen(other.address) + 1];
	strcpy(address, other.address);
	customers = other.customers;
	accounts = other.accounts;
	bankInterestRate = other.bankInterestRate;
	bankOverdraft = other.bankOverdraft;
}

void Bank::free()
{
	delete[] name;
	delete[] address;
}

void Bank::menu() const
{
	int choice;
	std::cout << "\t\t Create a new bank \n\n" << std::endl;;
	char bankName[BUFFER_LINE_SIZE] = "";
	std::cout << "\t Enter bank name: ";
	std::cin >> bankName;
	std::cout << "\t Enter bank adress:";
	char bankAddress[BUFFER_LINE_SIZE] = "";
	std::cin >> bankAddress;
	std::cout << "\t Enter bank overdraft:";
	int overdraft = 0;
	std::cin >> overdraft;
	std::cout << "\t Enter bank interest rate:";
	int interestRate = 0;
	std::cin >> interestRate;
	Bank bank(bankName, bankAddress, overdraft, interestRate);
	std::cout << "\t\t BANK SYSTEM \n\n" << std::endl;
	while (true)
	{
		std::cout << "\t Choose from the menu below: \n" << std::endl;
		std::cout << "\t 1.Edit " << std::endl;
		std::cout << "\t 2.List " << std::endl;
		std::cout << "\t 3.Action " << std::endl;
		std::cout << "\t 4.Display info for the bank " << std::endl;
		std::cout << "\t 5.Quit \n" << std::endl;
		std::cout << "\t\t Enter your choice: ";

		std::cin >> choice;
		std::cout << std::endl;

		if (choice != 5)
		{
			int choice2;
			int choice3;
			if (choice == 1)
			{
				std::cout << "\t 1.Edit customer " << std::endl;
				std::cout << "\t 2.Edit account \n" << std::endl;
				std::cout << "\t\t Enter your choice: ";
				std::cin >> choice2;
				std::cout << std::endl;

				if (choice2 == 1)
				{
					std::cout << "\t 1.Add new customer " << std::endl;
					std::cout << "\t 2.Delete customer \n" << std::endl;
					std::cout << "\t\t Enter your choice: ";
					std::cin >> choice3;
					std::cout << std::endl;

					if (choice3 == 1)
					{
						char inputName[BUFFER_LINE_SIZE] = "";
						std::cout << "Enter name: " << std::endl;
						std::cin >> inputName;
						char inputAddress[BUFFER_LINE_SIZE] = "";
						std::cout << "Enter address: " << std::endl;
						std::cin >> inputAddress;
						char inputId[BUFFER_LINE_SIZE] = "";
						std::cout << "Enter id: " << std::endl;
						std::cin >> inputId;
						Customer customerToAdd(inputId, inputName, inputAddress);
						bank.addCustomer(customerToAdd);
					}
					else if (choice3 == 2)
					{
						char inputId[1024] = "";
						std::cout << "Enter customer Id: " << std::endl;
						std::cin >> inputId;
						bank.deleteCustomer(inputId);
					}
					else std::cout << "Invalid number. Please try again: ";
					std::cout << std::endl;
				}
				else if (choice2 == 2)
				{
					std::cout << "\t 1.Add new account " << std::endl;
					std::cout << "\t 2.Delete account \n" << std::endl;
					std::cout << "\t\t Enter your choice: ";
					std::cin >> choice3;
					std::cout << std::endl;

					if (choice3 == 1)
					{
						char inputTypeAccount[1024] = "";
						std::cout << "Enter type of account(Normal, Privilege, Savings): " << std::endl;
						std::cin >> inputTypeAccount;
						char inputUssername[1024] = "";
						std::cout << "Enter username: " << std::endl;
						std::cin >> inputUssername;
						char inputPassword[1024] = "";
						std::cout << "Enter password: " << std::endl;
						std::cin >> inputPassword;
						char inputIban[1024] = "";
						std::cout << "Enter iban: " << std::endl;
						std::cin >> inputIban;
						char inputId[1024] = "";
						std::cout << "Enter Id: " << std::endl;
						std::cin >> inputId;
						double inputAmount;
						std::cout << "Enter amount: " << std::endl;
						std::cin >> inputAmount;
						char inputDate[1024] = "";
						std::cout << "Enter date: " << std::endl;
						std::cin >> inputDate;
						if (strcmp(inputTypeAccount, "Normal") == 0)
						{
							NormalAccount accountToAdd(inputUssername, inputPassword, inputIban, inputId, inputAmount, inputDate);
							bank.addAccount(accountToAdd);
						}
						else if (strcmp(inputTypeAccount, "Savings") == 0)
						{
							SavingsAccount accountToAdd(inputUssername, inputPassword, inputIban, inputId, inputAmount, inputDate, bank.getInterestRate());
							bank.addAccount(accountToAdd);
						}
						else if (strcmp(inputTypeAccount, "Privilege") == 0)
						{
							PrivilegeAccount accountToAdd(inputUssername, inputPassword, inputIban, inputId, inputAmount, inputDate, bank.getOverdraft());
							bank.addAccount(accountToAdd);
						}
					}
					else if (choice3 == 2)
					{
						char inputId[1024] = "";
						std::cout << "Enter account Id: " << std::endl;
						std::cin >> inputId;
						bank.deleteAccount(inputId);
					}
					else std::cout << "Invalid number. Please try again: ";
					std::cout << std::endl;
				}
				else std::cout << "Invalid number. Please try again: ";
			}
			else if (choice == 2)
			{
				std::cout << "\t 1.List all customers " << std::endl;
				std::cout << "\t 2.List all accounts " << std::endl;
				std::cout << "\t 3.List customer account " << std::endl;
				std::cout << "\t 4.List log \n" << std::endl;
				std::cout << "\t\t Enter your choice: ";
				std::cin >> choice2;
				std::cout << std::endl;

				if (choice2 == 1)
				{
					bank.listCustomers();
				}
				else if (choice2 == 2)
				{
					bank.listAccounts();
				}
				else if (choice2 == 3)
				{
					char inputId[BUFFER_LINE_SIZE] = "";
					std::cout << "Enter id: " << std::endl;
					std::cin >> inputId;
					bank.listCustomerAccount(inputId);
				}
				else if (choice2 == 4)
				{
					std::ifstream inputFile("transaction.txt");

					if (!inputFile.is_open())
					{
						std::cout << "Can not open the file!" << std::endl;
						return;
					}

					while (!inputFile.eof())
					{
						char buffer[BUFFER_LINE_SIZE];
						inputFile.getline(buffer, BUFFER_LINE_SIZE);
						std::cout << buffer << std::endl;
					}

					inputFile.close();
				}
				else "Invalid number. Try again: ";
			}
			else if (choice == 3)
			{
				std::cout << "\t 1.Withdraw from account " << std::endl;
				std::cout << "\t 2.Deposit to account " << std::endl;
				std::cout << "\t 3.Transfer \n" << std::endl;
				std::cout << "\t\t Enter your choice: ";
				std::cin >> choice2;
				std::cout << std::endl;

				if (choice2 == 1)
				{
					char inputId[1024] = "";
					std::cout << "Enter id: " << std::endl;
					std::cin >> inputId;
					double inputMoney = 0;
					std::cout << "Enter money: " << std::endl;
					std::cin >> inputMoney;
					bank.withdrawFromAccount(inputId, inputMoney);
					bank.exportLog("Money withdrowed!");
				}
				else if (choice2 == 2)
				{
					char inputId[BUFFER_LINE_SIZE] = "";
					std::cout << "Enter id: " << std::endl;
					std::cin >> inputId;
					double inputMoney = 0;
					std::cout << "Enter money: " << std::endl;
					std::cin >> inputMoney;
					bank.depositToAccount(inputId, inputMoney);
					bank.exportLog("Money deposited!");
				}
				else if (choice2 == 3)
				{
					char firstIBAN[BUFFER_LINE_SIZE] = "";
					std::cout << "Enter first IBAN: " << std::endl;
					std::cin >> firstIBAN;
					char secondIBAN[BUFFER_LINE_SIZE] = "";
					std::cout << "Enter second IBAN: " << std::endl;
					std::cin >> secondIBAN;
					double inputMoney = 0;
					std::cout << "Enter money: " << std::endl;
					std::cin >> inputMoney;
					bank.transfer(inputMoney, firstIBAN, secondIBAN);
				}
				else "Invalid number. Try again: ";
			}
			else if (choice == 4)
			{
				bank.display();
			}
			else
			{
				std::cout << "Invalid number. Try again: ";
				std::cin >> choice;
				continue;
			}
		}
		else break;
	}
}