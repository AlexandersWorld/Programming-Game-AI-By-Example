class Bank
{

public:

	int m_iAmountOfMoney = 0;
	int Deposit(int amount);
	int WithDraw();

	static Bank* Instance();
};