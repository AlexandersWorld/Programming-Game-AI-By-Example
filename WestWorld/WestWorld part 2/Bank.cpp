#include "Bank.h"

int Bank::Deposit(int amount)
{
	m_iAmountOfMoney += amount;

	return m_iAmountOfMoney;
}

int Bank::WithDraw()
{
	int withdrawMoney = m_iAmountOfMoney;

	if (withdrawMoney > 0)
	{
		m_iAmountOfMoney = 0;
		return withdrawMoney;
	}
}

Bank* Bank::Instance()
{
	static Bank instance;

	return &instance;
}
