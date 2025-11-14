#include "Telegram.h"
#include <set>

class Entity;

class MessageDispatcher
{
private:
	std::set<Telegram> PriorityQ;

	void Discharge(Entity* pReceiver, const Telegram& msg);

	MessageDispatcher() {}

public:
	static MessageDispatcher* Instance();

	void DispatchMessage(double delay, int sender, int receiver, int msg, void* ExtraInfo);

	void DispatchDelayedMessages();
};

#define Dispatch MessageDispatcher::Instance();